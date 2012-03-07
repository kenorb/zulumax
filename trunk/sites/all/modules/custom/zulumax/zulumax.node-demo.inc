<?php

	define ('WorkflowDemoStateCreated',		2);
	define ('WorkflowDemoStateActivated',	3);
	define ('WorkflowDemoStateExpired',		4);

	/**
	 * Executed when the Demo content is being submitted
	 * @param array Variables from the submitted form
	 */
	function zulumax_node_demo_create ($vars, $isNew)
	{
		set_time_limit (3 * 60);
		
		require_once 'sites/all/modules/custom/deathbycaptcha/deathbycaptcha.module';
		
		$email				= $vars -> field_email ['und'] [0] ['value'];
		$balance			= $vars -> field_initial_balance ['und'] [0] ['value'];
		$accountName		= $vars -> field_account_name ['und'] [0] ['value'];
		$signalProviders	= $vars -> field_signal_providers ['und'];
		$accountActivated	= false;
		
		
		$curl = curl_init ();

		$headers					= array (
			'User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:9.0.1) Gecko/20100101 Firefox/9.0.1',
			'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,* / *;q=0.8',
			'Accept-Language: en-us;q=0.7,en;q=0.3',
			'Accept-Charset: utf-8;q=0.7,*;q=0.7',
			'Content-type: application/x-www-form-urlencoded',
			'Connection: keep-alive'
		);

		$cookieFile				= sys_get_temp_dir () . "/cookies-zulumax.txt";
		
		file_put_contents ($cookieFile, '');

		if (module_exists ('proxychanger'))
		// Using Proxy Changer
		{
			proxychanger_to_curl ($curl);
		}
		
		curl_setopt ($curl, CURLOPT_COOKIEJAR,		$cookieFile);
		curl_setopt ($curl, CURLOPT_COOKIEFILE,		$cookieFile);
		curl_setopt	($curl, CURLOPT_COOKIE,			session_name () . '=' . session_id ());
		curl_setopt ($curl, CURLOPT_URL,			'http://zulutrade.com/SignUp_Demo.aspx');
		curl_setopt ($curl, CURLOPT_REFERER,		'http://www.google.com/');
		curl_setopt ($curl, CURLOPT_AUTOREFERER,	1);
		curl_setopt ($curl, CURLOPT_FOLLOWLOCATION,	0);
		curl_setopt ($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt ($curl, CURLOPT_COOKIESESSION,  1);
		
		$content			= curl_exec ($curl);
		
		if ($content == '')
		{
			watchdog (t('Creating Demo account ' . $accountName), "Can't get content via this connection(or proxy)", array (), WATCHDOG_CRITICAL);
					
			drupal_set_message ('Creating Demo account ' . $accountName. ": Can't get content via this connection(or proxy)", 'error');
					
			return;
		}
		
		
		preg_match ('/__CVIEWSTATE" value="(.*?)"/si', $content, $matches);
		
		$viewState		= $matches [1];
		
		preg_match ('/bdcaptcha" value="(.*?)"/si', $content, $matches);
		
		$bdCaptcha		= $matches [1];
		
		
		preg_match ("/_CaptchaImage' src='(.*?)'/si", $content, $matches);
		
		$captchaURL		= 'http://zulutrade.com/' . $matches [1];
		
		$captchaId		= null;
		$tries			= 3;
		
		do
		{
			if ($captchaId)
				watchdog (t('Creating Demo account ' . $accountName), "Looks like captcha was incorrectly solved. We'll try again", array (), WATCHDOG_WARNING);
			
			$captchaText	= deathbycaptcha_solve_curl_url ($curl, $captchaURL, $captchaId);
			
			$fields = array (
				'LBD_VCT_signup_demo_ctl00_box1_personaldetails_captchaverification_bdcaptcha=' . urlencode ($bdCaptcha),
				'__CVIEWSTATE=' . urlencode ($viewState),
				'__EVENTARGUMENT=',
				'__EVENTTARGET=',
				'__VIEWSTATE=',
				'ctl00$box1$PersonalDetails$CaptchaVerification$TbGuess=' . urlencode ($captchaText),
				'ctl00$box1$PersonalDetails$DropDownListCountry=142',
				'ctl00$box1$PersonalDetails$DropDownListCourtesyTitle=Mr',
				'ctl00$box1$PersonalDetails$DropDownListState=1',
				'ctl00$box1$PersonalDetails$TbPhoneCountryCode=48',
				'ctl00$box1$PersonalDetails$TbPhoneNumber=234567890',
				'ctl00$box1$PersonalDetails$TextBoxEmail=' . urlencode ($email),
				'ctl00$box1$PersonalDetails$TextBoxFirstName=' . urlencode ($accountName),
				'ctl00$box1$PersonalDetails$TextBoxLastName=NotUsed',
				'ctl00$box1$PersonalDetails$TextBoxMiddleName=',
				'ctl00$box1$PersonalDetails$ddlBalance=3000',
				'ctl00$box1$PersonalDetails$ddlLamms=3001',
				'ctl00$box1$PersonalDetails$ddlLeverage=10',
				'ctl00$box1$PersonalDetails$txtBalance=' . urlencode ($balance),
				'ctl00$box1$ctl00=Create my Demo Account'
			);
			
			$postFields = implode ('&', $fields);
			
			curl_setopt ($curl, CURLOPT_URL,			'http://zulutrade.com/SignUp_Demo.aspx?Lang=en');
			curl_setopt ($curl, CURLOPT_HTTPHEADER,		array_merge ($headers, array ('Content-length: ' . strlen ($postFields))));
	 		curl_setopt ($curl, CURLOPT_POST,			1);
	 		curl_setopt ($curl, CURLOPT_POSTFIELDS,		$postFields);
	 		curl_setopt ($curl, CURLOPT_VERBOSE,		0);
	 		curl_setopt ($curl, CURLOPT_FOLLOWLOCATION,	1);
	 		curl_setopt ($curl, CURLOPT_RETURNTRANSFER,	1);
	 		
	 		$content = curl_exec ($curl);
	 		
	 		if (strpos ($content, 'you have exceeded the maximum') !== false)
	 		// We can't create more accounts
	 		{
				if (module_exists ('proxychanger'))
				// Trying to renew proxy
				{
					if (!proxychanger_renew_proxy ($alreadyUsedProxies))
					{
	 					watchdog (t('Creating Demo account ' . $accountName), "Account limit exceeded for this IP and no more proxies to use", array (), WATCHDOG_WARNING);
	 			
	 					drupal_set_message ('Creating Demo account ' . $accountName. ": Account limit exceeded for this IP and no more proxies to use", 'error');
					}
					
					proxychanger_to_curl ($curl);
				}
	 			
	 			
	 			watchdog (t('Creating Demo account ' . $accountName), "Account limit exceeded for this IP", array (), WATCHDOG_WARNING);
	 			
	 			drupal_set_message ('Creating Demo account ' . $accountName. ": Account limit exceeded for this IP", 'error');
	 			
	 			return;
	 		}
	 		
		}
	 	while (strpos ($content, "message: 'Please type the letters") !== false && --$tries > 0);
 		
		curl_close ($curl);
		
		
		//
		// Retrieving activation link
		//
		
		$curl = curl_init ();
		
		curl_setopt ($curl, CURLOPT_FOLLOWLOCATION,	1);
		curl_setopt ($curl, CURLOPT_RETURNTRANSFER,	1);

		$tries = 10;
		
		sleep (3);
		
		while ($tries--)
		{
			curl_setopt ($curl, CURLOPT_URL, 'http://niepodam.pl/users/' . substr ($email, 0, strpos ($email, '@')));
			$content = curl_exec ($curl);
			
			preg_match ('%/wiadomosci/([0-9]+)%si', $content, $matches);
			
			$messageId = @$matches [1];
			
			if (!$messageId)
			// No mail yet
			{
				if (!$tries)
				{
					watchdog (t('Creating Demo account ' . $accountName), "No activation mail received. I tried 10 times with no success", array (), WATCHDOG_CRITICAL);
					
					drupal_set_message ('Creating Demo account ' . $accountName. ": No activation mail received. I tried 10 times with no success", 'error');
					
					return;
				}
				
				watchdog (t('Creating Demo account ' . $accountName), "No activation mail received yet", array (), WATCHDOG_WARNING);
				
				sleep (3);
				
				continue;
			}
			
			// Reading new message
			curl_setopt ($curl, CURLOPT_URL, 'http://niepodam.pl/wiadomosci/' . $messageId);
			$content = curl_exec ($curl);

			preg_match ('%Username:.*?>([A-Z0-9]+)<%si', $content, $matches);
			$finalUserName = $matches [1];
			
			preg_match ('%Password:.*?>([A-Za-z0-9]+)<%si', $content, $matches);
			$finalUserPassword = $matches [1];

			// Finding activation link
			preg_match ('%"(http://zulutrade\.com/SignUp Activation\.aspx.*?)"%si', $content, $matches);
			$activationLink	= $matches [1];
			$activationLink	= str_replace (' ', '_', $activationLink) . '&Lang=en';
			
			sleep (2);
				
			// Opening activation link
			curl_setopt ($curl, CURLOPT_URL, $activationLink);
			$content = curl_exec ($curl);
			
			file_put_contents ('C:\activation-result.htm', $content);
			
			if (strpos ($content, 'ctl00$box1$tbPassword') !== false)
			// Good. Allows us to log in
				$accountActivated = true;
			
			break;
		}
		
		$vars -> field_user_name			= array ('und' => array (array ('value' => $finalUserName)));
		$vars -> field_user_password		= array ('und' => array (array ('value' => $finalUserPassword)));
		
		field_attach_presave ('node',	$vars);
		
		field_attach_update ('node',	$vars);
		
		if ($accountActivated)
		{
			workflow_transition ($vars, WorkflowDemoStateActivated);
			
			drupal_set_message (t("Account activated. You can log in to ZuluTrade using credentials: $finalUserName / $finalUserPassword."));
		}
		else
			drupal_set_message (t("Account has not yet been activated. Probably an activation mail wasn't received."), 'warning');
		
		curl_close ($curl);
	}

?>