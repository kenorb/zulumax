<?php

	/**
	 * Generates content for main admin configuration page 
	 * @return string
	 */
	function tor_admin_config_page ()
	{
		$output = drupal_get_form ('tor_admin_form');
	
		return $output;
	}

	/**
	 * Generates configuration form
	 * @param array $form
	 * @param array $form_state
	 * @return array
	 */
	function tor_admin_form ($form, &$form_state)
	{
		$configuration = tor_get_config ();

	  $form ['source'] = array (
	  
	  	array (
	  		'#title'					=> t('General settings'),
	  		'#type'						=> 'fieldset',
	  	
		  	'torServerIP'				=> array (
			    '#type'						=> 'textfield',
			    '#title'					=> t('TOR Server IP'),
			    '#default_value'	=> @$form_state ['torServerIP'] ? @$form_state ['torServerIP'] : @$configuration -> torServerIP,
			    '#maxlength'			=> 15,
			    '#size'						=> 45,
			    '#description'		=> '',
			    '#required'				=> TRUE
			   ),
				 
		  	'torServerPort'			=> array (
			    '#type'						=> 'textfield',
			    '#title'					=> t('TOR Server Port'),
			    '#default_value'	=> @$form_state ['torServerPort'] ? @$form_state ['torServerPort'] : @$configuration -> torServerPort,
			    '#maxlength'			=> 5,
			    '#size'						=> 15,
			    '#description'		=> '',
			    '#required'				=> TRUE
			   ),
			   
		  	'torserverControlPort' => array (
			    '#type'						=> 'textfield',
			    '#title'					=> t('TOR Server Service Port'),
			    '#default_value'	=> @$form_state ['torserverControlPort'] ? @$form_state ['torserverControlPort'] : @$configuration -> torserverControlPort,
			    '#maxlength'			=> 5,
			    '#size'						=> 15,
			    '#description'		=> '',
			    '#required'				=> TRUE
			   ),
			   
		  	'torserverControlPassword' => array (
			    '#type'						=> 'textfield',
			    '#title'					=> t('TOR Server Service Password'),
			    '#default_value'	=> @$form_state ['torserverControlPassword'] ? @$form_state ['torserverControlPassword'] : @$configuration -> torserverControlPassword,
			    '#maxlength'			=> 32,
			    '#size'						=> 45,
			    '#description'		=> '',
			    '#required'				=> TRUE
			   ),
			   
		  	'torServerIPsPool' => array (
			    '#type'						=> 'textfield',
			    '#title'					=> t('TOR Server IPs Pool'),
			    '#default_value'	=> @$form_state ['torServerIPsPool'] ? @$form_state ['torServerIPsPool'] : @$configuration -> torServerIPsPool,
			    '#maxlength'			=> 3,
			    '#size'						=> 8,
			    '#description'		=> '',
			    '#required'				=> TRUE
			   ),
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
	function tor_admin_form_validate ($form, &$form_state)
	{
	}
	
	/**
	 * Called when configuration form is being submitted
	 * @param array $form
	 * @param array $form_state
	 */
	function tor_admin_form_submit ($form, &$form_state)
	{
	  // Remove unnecessary values.
	  form_state_values_clean ($form_state);
	
	  tor_admin_form_save ($form_state ['values']);
	
	  drupal_set_message (t('Configuration saved.'));
	  
	  $form_state ['redirect'] = 'admin/config/tor';
	}
	
	/**
	 * Saves configuration form variables into the database
	 * @param array $values Validated fields' data
	 * @return array
	 */
	function tor_admin_form_save ($values)
	{
		variable_set ('tor_serverIP',								$values ['torServerIP']);
		variable_set ('tor_serverPort',							$values ['torServerPort']);
		variable_set ('tor_serverControlPort',			$values ['torserverControlPort']);
		variable_set ('tor_serverControlPassword',	$values ['torserverControlPassword']);
		variable_set ('tor_serverIPsPool',					$values ['torServerIPsPool']);
		
		drupal_set_message ('Current TOR IP: ' . tor_get_current_ip ());
	}

?>