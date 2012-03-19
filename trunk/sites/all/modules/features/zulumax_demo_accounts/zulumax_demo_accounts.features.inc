<?php
/**
 * @file
 * zulumax_demo_accounts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function zulumax_demo_accounts_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function zulumax_demo_accounts_node_info() {
  $items = array(
    'demo' => array(
      'name' => t('Demo'),
      'base' => 'node_content',
      'description' => t('Represents a physical demo account of ZuluTrade system'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_workflow_features_default_workflow().
 */
function zulumax_demo_accounts_workflow_features_default_workflow() {
  return array(
    'Demo account state' => array(
      'name' => 'Demo account state',
      'tab_roles' => '3',
      'options' => 'a:3:{s:16:"comment_log_node";i:0;s:15:"comment_log_tab";i:0;s:13:"name_as_title";i:1;}',
      'states' => array(
        0 => array(
          'state' => '(creation)',
          'weight' => '-50',
          'sysid' => '1',
          'status' => '1',
        ),
        1 => array(
          'state' => 'created',
          'weight' => '0',
          'sysid' => '0',
          'status' => '1',
        ),
        2 => array(
          'state' => 'activated',
          'weight' => '0',
          'sysid' => '0',
          'status' => '1',
        ),
        3 => array(
          'state' => 'expired',
          'weight' => '0',
          'sysid' => '0',
          'status' => '1',
        ),
      ),
      'transitions' => array(
        0 => array(
          'sid' => '(creation)',
          'target_sid' => 'created',
          'roles' => 'author,3',
        ),
        1 => array(
          'sid' => '(creation)',
          'target_sid' => 'activated',
          'roles' => 'author,3',
        ),
        2 => array(
          'sid' => '(creation)',
          'target_sid' => 'expired',
          'roles' => 'author,3',
        ),
        3 => array(
          'sid' => 'created',
          'target_sid' => 'activated',
          'roles' => 'author,3',
        ),
        4 => array(
          'sid' => 'created',
          'target_sid' => 'expired',
          'roles' => 'author,3',
        ),
        5 => array(
          'sid' => 'activated',
          'target_sid' => 'created',
          'roles' => 'author,3',
        ),
        6 => array(
          'sid' => 'activated',
          'target_sid' => 'expired',
          'roles' => 'author,3',
        ),
        7 => array(
          'sid' => 'expired',
          'target_sid' => 'created',
          'roles' => 'author,3',
        ),
        8 => array(
          'sid' => 'expired',
          'target_sid' => 'activated',
          'roles' => 'author,3',
        ),
      ),
      'node_types' => array(
        0 => array(
          'type' => 'demo',
          'wid' => '1',
        ),
      ),
    ),
  );
}
