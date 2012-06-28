<?php

/**
 * Generates content for main admin configuration page 
 * @return string
 */
function deathbycaptcha_admin_config_page ()
{
  $output = drupal_get_form ('deathbycaptcha_admin_form');

  return $output;
}

/**
 * Generates configuration form
 * @param array $form
 * @param array $form_state
 * @return array
 */
function deathbycaptcha_admin_form ($form, &$form_state)
{
  $configuration = deathbycaptcha_get_config ();

  $form ['source'] = array (
  
    array (
      '#title'					=> t('User credentials'),
      '#type'						=> 'fieldset',
    
      'userName'				=> array (
        '#type'						=> 'textfield',
        '#title'					=> t('User name'),
        '#default_value'	=> @$form_state ['userName'] ? @$form_state ['userName'] : $configuration -> userName,
        '#maxlength'			=> 64,
        '#size'						=> 45,
        '#description'		=> '',
        '#required'				=> TRUE
       ),
       
      'userPassword'			=> array (
        '#type'						=> 'textfield',
        '#title'					=> t('User password'),
        '#default_value'	=> @$form_state ['userPassword'] ? @$form_state ['userPassword'] : $configuration -> userPassword,
        '#maxlength'			=> 64,
        '#size'						=> 45,
        '#description'		=> '',
        '#required'				=> TRUE
      )
    ),
    array (
    
      '#title'					=> t('Connection settings'),
      '#type'						=> 'fieldset',
     
      'timeout'					=> array (
        '#type'						=> 'textfield',
        '#title'					=> t('Captch solving timeout'),
        '#default_value'	=> @$form_state ['timeout'] ? @$form_state ['timeout'] : $configuration -> timeout,
        '#maxlength'			=> 4,
        '#size'						=> 10,
        '#description'		=> 'In seconds'
      )
    )
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
function deathbycaptcha_admin_form_validate ($form, &$form_state)
{
  $values = $form_state ['values'];
  
  if (!empty ($values ['userName']) && !empty ($values ['userPassword']))
  {
    $balance = deathbycaptcha_check_credentials ($values ['userName'], $values ['userPassword']);
    
    if ($balance === null)
      form_set_error ($values ['userName'], t("Specified account doesn't exist or DeathByCaptcha server is down(which is rather the latest possibility)"));
    else
      drupal_set_message ('Sucessfully configured DeathByCaptcha account. Account balance: $' . $balance);
  }
}

/**
 * Called when configuration form is being submitted
 * @param array $form
 * @param array $form_state
 */
function deathbycaptcha_admin_form_submit ($form, &$form_state)
{
  // Remove unnecessary values.
  form_state_values_clean ($form_state);

  deathbycaptcha_admin_form_save ($form_state ['values']);

  drupal_set_message (t('Configuration saved.'));
  
  $form_state ['redirect'] = 'admin/config/deathbycaptcha';
}

/**
 * Saves configuration form variables into the database
 * @param array $values Validated fields' data
 * @return array
 */
function deathbycaptcha_admin_form_save ($values)
{
  variable_set ('deathbycaptcha_userName',			$values ['userName']);
  variable_set ('deathbycaptcha_userPassword',	$values ['userPassword']);
  variable_set ('deathbycaptcha_timeout',				$values ['timeout']);
}

