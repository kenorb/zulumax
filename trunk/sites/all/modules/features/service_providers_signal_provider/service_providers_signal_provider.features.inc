<?php
/**
 * @file
 * service_providers_signal_provider.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function service_providers_signal_provider_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function service_providers_signal_provider_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}
