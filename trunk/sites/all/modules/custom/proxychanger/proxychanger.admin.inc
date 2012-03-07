<?php

	/**
	 * Generates content for main admin configuration page 
	 * @return string
	 */
	function proxychanger_admin_config_page ()
	{
		$output = drupal_get_form ('proxychanger_admin_form');
	
		return $output;
	}

	/**
	 * Generates configuration form
	 * @param array $form
	 * @param array $form_state
	 * @return array
	 */
	function proxychanger_admin_form ($form, &$form_state)
	{
		$configuration = proxychanger_get_config ();

		$form ['source'] = array (
		
			array (
				'#title'					=> t('General settings'),
				'#type'						=> 'fieldset',
			
				'proxyChangerEnabled'		=> array (
					'#type'					=> 'checkbox',
					'#title'				=> t('Enable Proxy Changer'),
					'#default_value'		=> @$form_state ['proxyChangerEnabled'] ? @$form_state ['proxyChangerEnabled'] : @$configuration -> proxyChangerEnabled,
					'#required'				=> FALSE
				 ),
				 
				'proxyChangerServers'		=> array (
					'#type'					=> 'textarea',
					'#title'				=> t('List of proxies'),
					'#default_value'		=> @$form_state ['proxyChangerServers'] ? @$form_state ['proxyChangerServers'] : @$configuration -> proxyChangerServers,
					'#maxlength'			=> 16384,
					'#size'					=> 45,
					'#description'			=> 'Format: IP:Port[@UserName:Password], e.g.: 123.45.67.89:8080 or 123.45.67.89:8080@lt:pass123',
					'#required'				=> FALSE
				 )
		),
		);
	
		$form ['actions'] = array ('#type' => 'actions');
		
		$form ['actions']['submit'] = array
		(
			'#type'		=> 'submit',
			'#value'	=> t('Save'),
		);
		
		return $form;
	}
	
	
	/**
	 * Validates the configuration form
	 * @param array $form
	 * @param array $form_state
	 */
	function proxychanger_admin_form_validate ($form, &$form_state)
	{
		$values = $form_state ['values'];
		
		if (!empty ($values ['proxyChangerServers']))
		{
			$errorEncountered = false;
			
			$oldServerList = variable_get ('proxyChangerServers', ''); 
			
			variable_set ('proxyChangerServers', $values ['proxyChangerServers']);

			$servers = proxychanger_get_server_list (true);
			
			if ($servers)
			{
				foreach ($servers as $serverId => $server)
				{
					if (!@$server -> serverAddress)
					{
						form_set_error ($values ['proxyChangerServers'], 'Server in line ' . ($serverId + 1) . ': ' . t("Could not deduce server IP address"));
						
						$errorEncountered = true;
					}
					
					if (!@$server -> serverPort)
					{
						form_set_error ($values ['proxyChangerServers'], 'Server in line ' . ($serverId + 1) . '(' . $server -> serverAddress . '): ' . t("Could not deduce server port number"));
						
						$errorEncountered = true;
					}
					
					if (@$server -> userName && !@$server -> userPassword || !@$server -> userName && @$server -> userPassword)
					{
						form_set_error ($values ['proxyChangerServers'], 'Server in line ' . ($serverId + 1) . '(' . $server -> serverAddress . '): ' . t("You must pass none or both, user name and user password"));
						
						$errorEncountered = true;
					}
				}
			}
				
			if ($errorEncountered)
			// Reverting server list
				variable_set ('proxyChangerServers', $oldServerList);
		}
	}
	
	/**
	 * Called when configuration form is being submitted
	 * @param array $form
	 * @param array $form_state
	 */
	function proxychanger_admin_form_submit ($form, &$form_state)
	{
		// Remove unnecessary values.
		form_state_values_clean ($form_state);
	
		proxychanger_admin_form_save ($form_state ['values']);
	
		drupal_set_message (t('Configuration saved.'));
		
		$form_state ['redirect'] = 'admin/config/proxychanger';
	}
	
	/**
	 * Saves configuration form variables into the database
	 * @param array $values Validated fields' data
	 * @return array
	 */
	function proxychanger_admin_form_save ($values)
	{
		variable_set ('proxyChangerServers',		$values ['proxyChangerServers']);
		
		if (!proxychanger_get_server_list (true) && $values ['proxyChangerEnabled'])
		{
			variable_set ('proxyChangerEnabled',	false);
			
			drupal_set_message (t('No servers in the list, Proxy Changer disabled'));
		}
		else
			variable_set ('proxyChangerEnabled',	$values ['proxyChangerEnabled']);
		
		variable_set ('proxyChangerServerCurrent',	0);
		
	}

?>