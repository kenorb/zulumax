<?php
/**
 * @file
 * service_providers.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function service_providers_field_group_info() {
  $export = array();

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_community|node|signal_provider|form';
  $field_group->group_name = 'group_community';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'signal_provider';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Community',
    'weight' => '5',
    'children' => array(
      0 => 'field_messages',
      1 => 'field_avg_rating',
      2 => 'field_total_votes',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_community|node|signal_provider|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_history|node|signal_provider|form';
  $field_group->group_name = 'group_history';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'signal_provider';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'History',
    'weight' => '15',
    'children' => array(
      0 => 'field_csv_file',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_history|node|signal_provider|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_popularity|node|signal_provider|form';
  $field_group->group_name = 'group_popularity';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'signal_provider';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Popularity',
    'weight' => '4',
    'children' => array(
      0 => 'field_followers',
      1 => 'field_has_live_followers',
      2 => 'field_ranking',
      3 => 'field_profile_viewed',
      4 => 'field_balance_of_live_accounts',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_popularity|node|signal_provider|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile|node|signal_provider|form';
  $field_group->group_name = 'group_profile';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'signal_provider';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Profile',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_known_as',
      2 => 'field_running_weeks',
      3 => 'field_updated_on',
      4 => 'field_account_type',
      5 => 'field_sp_id',
      6 => 'field_strategy_name',
      7 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_profile|node|signal_provider|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profit|node|signal_provider|form';
  $field_group->group_name = 'group_profit';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'signal_provider';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Profit',
    'weight' => '2',
    'children' => array(
      0 => 'field_profit',
      1 => 'field_avg_pips_trade',
      2 => 'field_max_drawdown',
      3 => 'field_necessary_minimum_equity',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_profit|node|signal_provider|form'] = $field_group;

  $field_group = new stdClass;
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_trades|node|signal_provider|form';
  $field_group->group_name = 'group_trades';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'signal_provider';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Trades',
    'weight' => '1',
    'children' => array(
      0 => 'field_trades',
      1 => 'field_winning_trades',
      2 => 'field_avg_trade_time',
      3 => 'field_max_open_trades',
      4 => 'field_worst_trade',
      5 => 'field_best_trade',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_trades|node|signal_provider|form'] = $field_group;

  return $export;
}
