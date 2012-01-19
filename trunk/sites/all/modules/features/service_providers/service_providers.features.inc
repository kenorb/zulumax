<?php
/**
 * @file
 * service_providers.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function service_providers_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function service_providers_node_info() {
  $items = array(
    'signal_provider' => array(
      'name' => t('Signal Provider'),
      'base' => 'node_content',
      'description' => t('Signal providers provide FX signals for all clients who select them in their accounts settings page.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
