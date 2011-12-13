<?php
/**
 * @file
 * followers.features.inc
 */

/**
 * Implements hook_node_info().
 */
function followers_node_info() {
  $items = array(
    'follower' => array(
      'name' => t('Follower'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
