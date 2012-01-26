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
		require_once 'sites/all/modules/custom/deathbycaptcha/deathbycaptcha.module';
		
		$moduleEnabledTOR = module_exists ('tor');
		
		if ($moduleEnabledTOR)
			require_once 'sites/all/modules/custom/tor/tor.module';

		$email						= $vars -> field_email ['und'] [0] ['value'];
		$balance					= $vars -> field_initial_balance ['und'] [0] ['value'];
		$accountName			= $vars -> field_account_name ['und'] [0] ['value'];
		$signalProviders	= $vars -> field_signal_providers ['und'];
		
		
		$curl = curl_init ();

		$headers					= array (
			'User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:9.0.1) Gecko/20100101 Firefox/9.0.1',
			'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
			'Accept-Language: en-us;q=0.7,en;q=0.3',
			'Accept-Charset: utf-8;q=0.7,*;q=0.7',
			'Content-type: application/x-www-form-urlencoded',
			'Connection: keep-alive'
		);

		$cookieFile				= sys_get_temp_dir () . "/cookies-zulumax.txt";
		
		file_put_contents ($cookieFile, '');

		if ($moduleEnabledTOR)
		{
			tor_renew_ip ();
			
			tor_to_curl ($curl);
		}
		
		curl_setopt ($curl, CURLOPT_COOKIEJAR,			$cookieFile);
		curl_setopt ($curl, CURLOPT_COOKIEFILE,			$cookieFile);
		curl_setopt	($curl, CURLOPT_COOKIE,					session_name () . '=' . session_id ());
		curl_setopt ($curl, CURLOPT_URL,						'http://zulutrade.com/SignUp_Demo.aspx');
		curl_setopt ($curl, CURLOPT_REFERER,				'http://www.google.com/');
		curl_setopt ($curl, CURLOPT_AUTOREFERER,		1);
		curl_setopt ($curl, CURLOPT_FOLLOWLOCATION,	0);
		curl_setopt ($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt ($curl, CURLOPT_COOKIESESSION,  1);
		
		$content			= curl_exec ($curl);
		
		preg_match ('/__CVIEWSTATE" value="(.*?)"/si', $content, $matches);
		
		$viewState		= $matches [1];
		
		preg_match ('/bdcaptcha" value="(.*?)"/si', $content, $matches);
		
		$bdCaptcha		= $matches [1];
		
		
		preg_match ("/_CaptchaImage' src='(.*?)'/si", $content, $matches);
		
		$captchaURL		= 'http://zulutrade.com/' . $matches [1];
		
		$captchaText	= '12345';//deathbycaptcha_solve_curl_url ($curl, $captchaURL, $captchaId);
		
		echo 'Captcha solved: <' . $captchaText . "> from " . $captchaURL . "\n";
		
		
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
		
		curl_setopt ($curl, CURLOPT_URL,						'http://zulutrade.com/SignUp_Demo.aspx');
		curl_setopt ($curl, CURLOPT_HTTPHEADER,			array_merge ($headers, array ('Content-length: ' . strlen ($postFields))));
 		curl_setopt ($curl, CURLOPT_POST,						1);
 		curl_setopt ($curl, CURLOPT_POSTFIELDS,			$postFields);
 		curl_setopt ($curl, CURLOPT_VERBOSE,				0);
 		curl_setopt ($curl, CURLOPT_FOLLOWLOCATION,	1);
 		curl_setopt ($curl, CURLOPT_RETURNTRANSFER,	1);
 		
 		//$content = curl_exec ($curl);
 		$content = '';
 		
 		file_put_contents ('C:\test.htm', $content);
 		
		curl_close ($curl);
		
		
		/*
		 * Retrieving activation link
		 */
		
		$curl = curl_init ();
		
		curl_setopt ($curl, CURLOPT_FOLLOWLOCATION,	1);
		curl_setopt ($curl, CURLOPT_RETURNTRANSFER,	1);

		$tries = 10;
		
		while ($tries--)
		{
			sleep (2);
			
			curl_setopt ($curl, CURLOPT_URL, 'http://niepodam.pl/users/' . substr ($email, 0, strpos ($email, '@')));
			$content = curl_exec ($curl);
			
			preg_match ('%/wiadomosci/([0-9]+)%si', $content, $matches);
			
			$messageId = $matches [1];
			
			if (!$messageId)
			// No mail yet
				continue;
			
			// Reading new message
			curl_setopt ($curl, CURLOPT_URL, 'http://niepodam.pl/wiadomosci/' . $messageId);
			$content = curl_exec ($curl);

			file_put_contents ('C:\ss.htm', $content);
			
			preg_match ('%Username:.*?>([A-Z0-9]+)<%si', $content, $matches);
			$finalUserName = $matches [1];
			
			preg_match ('%Password:.*?>([A-Za-z0-9]+)<%si', $content, $matches);
			$finalUserPassword = $matches [1];

			// Finding activation link
			preg_match ('%"(http://zulutrade\.com/SignUp_Activation\.aspx.*?)"%si', $content, $matches);
			$activationLink = $matches [1];
				
			// Opening activation link
			curl_setopt ($curl, CURLOPT_URL, $activationLink);
			$content = curl_exec ($curl);
			
			break;
		}
		
		$vars -> field_user_name			= array ('und' => array ('value' => $finalUserName));
		$vars -> field_user_password	= array ('und' => array ('value' => $finalUserPassword));
		
		node_save ($vars);
		
		curl_close ($curl);

		workflow_transition ($vars, WorkflowDemoStateActivated);
	}

?>