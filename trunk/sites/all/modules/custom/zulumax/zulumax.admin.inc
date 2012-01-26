<?php

	/**
	 * Generates content for main admin configuration page 
	 * @return string
	 */
	function zulumax_admin_config_page ()
	{
		$output = drupal_get_form ('zulumax_admin_form');
	
		return $output;
	}

	/**
	 * Generates configuration form
	 * @param array $form
	 * @param array $form_state
	 * @return array
	 */
	function zulumax_admin_form ($form, &$form_state)
	{
		$configuration = zulumax_get_config ();

	  $form ['source'] = array (
	  
	  	array (
	  		'#title'					=> t('General settings'),
	  		'#type'						=> 'fieldset',
	  	
		  	'userName'				=> array (
			    '#type'						=> 'textfield',
			    '#title'					=> t('Unused field'),
			    '#default_value'	=> @$form_state ['userName'] ? @$form_state ['userName'] : @$configuration -> userName,
			    '#maxlength'			=> 64,
			    '#size'						=> 45,
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
	function zulumax_admin_form_validate ($form, &$form_state)
	{
	}
	
	/**
	 * Called when configuration form is being submitted
	 * @param array $form
	 * @param array $form_state
	 */
	function zulumax_admin_form_submit ($form, &$form_state)
	{
	  // Remove unnecessary values.
	  form_state_values_clean ($form_state);
	
	  zulumax_admin_form_save ($form_state ['values']);
	
	  drupal_set_message (t('Configuration saved.'));
	  
	  $form_state ['redirect'] = 'admin/config/zulumax';
	}
	
	/**
	 * Saves configuration form variables into the database
	 * @param array $values Validated fields' data
	 * @return array
	 */
	function zulumax_admin_form_save ($values)
	{
		// variable_set ('zulumax_userName',			$values ['userName']);
	}

?>