<?php
/**
 * @file
 * service_providers_signal_provider.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function service_providers_signal_provider_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'performance';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Performance';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Performance';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'sort' => array(
      'bef_format' => 'bef',
      'combine' => 0,
      'reset' => 0,
      'reset_label' => '',
    ),
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Ranking */
  $handler->display->display_options['fields']['field_ranking']['id'] = 'field_ranking';
  $handler->display->display_options['fields']['field_ranking']['table'] = 'field_data_field_ranking';
  $handler->display->display_options['fields']['field_ranking']['field'] = 'field_ranking';
  $handler->display->display_options['fields']['field_ranking']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_ranking']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_ranking']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_ranking']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_ranking']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_ranking']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_ranking']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_ranking']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_ranking']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_ranking']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_ranking']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Average pips/trade */
  $handler->display->display_options['fields']['field_avg_pips_trade']['id'] = 'field_avg_pips_trade';
  $handler->display->display_options['fields']['field_avg_pips_trade']['table'] = 'field_data_field_avg_pips_trade';
  $handler->display->display_options['fields']['field_avg_pips_trade']['field'] = 'field_avg_pips_trade';
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_avg_pips_trade']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_avg_pips_trade']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_avg_pips_trade']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_avg_pips_trade']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '0',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_avg_pips_trade']['field_api_classes'] = 0;
  /* Field: Content: Average rating */
  $handler->display->display_options['fields']['field_avg_rating']['id'] = 'field_avg_rating';
  $handler->display->display_options['fields']['field_avg_rating']['table'] = 'field_data_field_avg_rating';
  $handler->display->display_options['fields']['field_avg_rating']['field'] = 'field_avg_rating';
  $handler->display->display_options['fields']['field_avg_rating']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_avg_rating']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_avg_rating']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_avg_rating']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_avg_rating']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_avg_rating']['field_api_classes'] = 0;
  /* Field: Content: Average trade time */
  $handler->display->display_options['fields']['field_avg_trade_time']['id'] = 'field_avg_trade_time';
  $handler->display->display_options['fields']['field_avg_trade_time']['table'] = 'field_data_field_avg_trade_time';
  $handler->display->display_options['fields']['field_avg_trade_time']['field'] = 'field_avg_trade_time';
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_avg_trade_time']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_avg_trade_time']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_avg_trade_time']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '0',
    'prefix_suffix' => 0,
  );
  $handler->display->display_options['fields']['field_avg_trade_time']['field_api_classes'] = 0;
  /* Field: Content: Followers */
  $handler->display->display_options['fields']['field_followers']['id'] = 'field_followers';
  $handler->display->display_options['fields']['field_followers']['table'] = 'field_data_field_followers';
  $handler->display->display_options['fields']['field_followers']['field'] = 'field_followers';
  $handler->display->display_options['fields']['field_followers']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_followers']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_followers']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_followers']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_followers']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_followers']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_followers']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_followers']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_followers']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_followers']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_followers']['field_api_classes'] = 0;
  /* Field: Content: Maximum drawdown */
  $handler->display->display_options['fields']['field_max_drawdown']['id'] = 'field_max_drawdown';
  $handler->display->display_options['fields']['field_max_drawdown']['table'] = 'field_data_field_max_drawdown';
  $handler->display->display_options['fields']['field_max_drawdown']['field'] = 'field_max_drawdown';
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_max_drawdown']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_max_drawdown']['empty'] = '0';
  $handler->display->display_options['fields']['field_max_drawdown']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_max_drawdown']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_max_drawdown']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  $handler->display->display_options['fields']['field_max_drawdown']['field_api_classes'] = 0;
  /* Field: Content: Running weeks */
  $handler->display->display_options['fields']['field_running_weeks']['id'] = 'field_running_weeks';
  $handler->display->display_options['fields']['field_running_weeks']['table'] = 'field_data_field_running_weeks';
  $handler->display->display_options['fields']['field_running_weeks']['field'] = 'field_running_weeks';
  $handler->display->display_options['fields']['field_running_weeks']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_running_weeks']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_running_weeks']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_running_weeks']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_running_weeks']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 0,
  );
  $handler->display->display_options['fields']['field_running_weeks']['field_api_classes'] = 0;
  /* Field: Content: SP ID */
  $handler->display->display_options['fields']['field_sp_id']['id'] = 'field_sp_id';
  $handler->display->display_options['fields']['field_sp_id']['table'] = 'field_data_field_sp_id';
  $handler->display->display_options['fields']['field_sp_id']['field'] = 'field_sp_id';
  $handler->display->display_options['fields']['field_sp_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_sp_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_sp_id']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_sp_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_sp_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_sp_id']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_sp_id']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_sp_id']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = 1;
  /* Field: Content: Total Trades */
  $handler->display->display_options['fields']['field_trades']['id'] = 'field_trades';
  $handler->display->display_options['fields']['field_trades']['table'] = 'field_data_field_trades';
  $handler->display->display_options['fields']['field_trades']['field'] = 'field_trades';
  $handler->display->display_options['fields']['field_trades']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_trades']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_trades']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_trades']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_trades']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_trades']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_trades']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_trades']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_trades']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_trades']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_trades']['field_api_classes'] = 0;
  /* Field: Content: Winning trades */
  $handler->display->display_options['fields']['field_winning_trades']['id'] = 'field_winning_trades';
  $handler->display->display_options['fields']['field_winning_trades']['table'] = 'field_data_field_winning_trades';
  $handler->display->display_options['fields']['field_winning_trades']['field'] = 'field_winning_trades';
  $handler->display->display_options['fields']['field_winning_trades']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_winning_trades']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_winning_trades']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_winning_trades']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_winning_trades']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_winning_trades']['field_api_classes'] = 0;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['body']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['body']['alter']['external'] = 0;
  $handler->display->display_options['fields']['body']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['body']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['body']['alter']['html'] = 0;
  $handler->display->display_options['fields']['body']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['body']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['body']['hide_empty'] = 0;
  $handler->display->display_options['fields']['body']['empty_zero'] = 0;
  $handler->display->display_options['fields']['body']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['body']['field_api_classes'] = 0;
  /* Field: Content: Profit */
  $handler->display->display_options['fields']['field_profit']['id'] = 'field_profit';
  $handler->display->display_options['fields']['field_profit']['table'] = 'field_data_field_profit';
  $handler->display->display_options['fields']['field_profit']['field'] = 'field_profit';
  $handler->display->display_options['fields']['field_profit']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_profit']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_profit']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_profit']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_profit']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_profit']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_profit']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_profit']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_profit']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_profit']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_profit']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_profit']['field_api_classes'] = 0;
  /* Sort criterion: Content: Ranking (field_ranking) */
  $handler->display->display_options['sorts']['field_ranking_value']['id'] = 'field_ranking_value';
  $handler->display->display_options['sorts']['field_ranking_value']['table'] = 'field_data_field_ranking';
  $handler->display->display_options['sorts']['field_ranking_value']['field'] = 'field_ranking_value';
  $handler->display->display_options['sorts']['field_ranking_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_ranking_value']['expose']['label'] = 'Ranking';
  /* Sort criterion: Content: Average pips/trade (field_avg_pips_trade) */
  $handler->display->display_options['sorts']['field_avg_pips_trade_value']['id'] = 'field_avg_pips_trade_value';
  $handler->display->display_options['sorts']['field_avg_pips_trade_value']['table'] = 'field_data_field_avg_pips_trade';
  $handler->display->display_options['sorts']['field_avg_pips_trade_value']['field'] = 'field_avg_pips_trade_value';
  $handler->display->display_options['sorts']['field_avg_pips_trade_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_avg_pips_trade_value']['expose']['label'] = 'Average pips/trade';
  /* Sort criterion: Content: Average rating (field_avg_rating) */
  $handler->display->display_options['sorts']['field_avg_rating_value']['id'] = 'field_avg_rating_value';
  $handler->display->display_options['sorts']['field_avg_rating_value']['table'] = 'field_data_field_avg_rating';
  $handler->display->display_options['sorts']['field_avg_rating_value']['field'] = 'field_avg_rating_value';
  $handler->display->display_options['sorts']['field_avg_rating_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_avg_rating_value']['expose']['label'] = 'Average rating';
  /* Sort criterion: Content: Average trade time (field_avg_trade_time) */
  $handler->display->display_options['sorts']['field_avg_trade_time_value']['id'] = 'field_avg_trade_time_value';
  $handler->display->display_options['sorts']['field_avg_trade_time_value']['table'] = 'field_data_field_avg_trade_time';
  $handler->display->display_options['sorts']['field_avg_trade_time_value']['field'] = 'field_avg_trade_time_value';
  $handler->display->display_options['sorts']['field_avg_trade_time_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_avg_trade_time_value']['expose']['label'] = 'Average trade time';
  /* Sort criterion: Content: Followers (field_followers) */
  $handler->display->display_options['sorts']['field_followers_value']['id'] = 'field_followers_value';
  $handler->display->display_options['sorts']['field_followers_value']['table'] = 'field_data_field_followers';
  $handler->display->display_options['sorts']['field_followers_value']['field'] = 'field_followers_value';
  $handler->display->display_options['sorts']['field_followers_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_followers_value']['expose']['label'] = 'Followers';
  /* Sort criterion: Content: Maximum drawdown (field_max_drawdown) */
  $handler->display->display_options['sorts']['field_max_drawdown_value']['id'] = 'field_max_drawdown_value';
  $handler->display->display_options['sorts']['field_max_drawdown_value']['table'] = 'field_data_field_max_drawdown';
  $handler->display->display_options['sorts']['field_max_drawdown_value']['field'] = 'field_max_drawdown_value';
  $handler->display->display_options['sorts']['field_max_drawdown_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_max_drawdown_value']['expose']['label'] = 'Maximum drawdown';
  /* Sort criterion: Content: Ranking (field_ranking) */
  $handler->display->display_options['sorts']['field_ranking_value_1']['id'] = 'field_ranking_value_1';
  $handler->display->display_options['sorts']['field_ranking_value_1']['table'] = 'field_data_field_ranking';
  $handler->display->display_options['sorts']['field_ranking_value_1']['field'] = 'field_ranking_value';
  $handler->display->display_options['sorts']['field_ranking_value_1']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_ranking_value_1']['expose']['label'] = 'Ranking';
  /* Sort criterion: Content: Running weeks (field_running_weeks) */
  $handler->display->display_options['sorts']['field_running_weeks_value']['id'] = 'field_running_weeks_value';
  $handler->display->display_options['sorts']['field_running_weeks_value']['table'] = 'field_data_field_running_weeks';
  $handler->display->display_options['sorts']['field_running_weeks_value']['field'] = 'field_running_weeks_value';
  $handler->display->display_options['sorts']['field_running_weeks_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_running_weeks_value']['expose']['label'] = 'Running weeks';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title';
  /* Sort criterion: Content: Total Trades (field_trades) */
  $handler->display->display_options['sorts']['field_trades_value']['id'] = 'field_trades_value';
  $handler->display->display_options['sorts']['field_trades_value']['table'] = 'field_data_field_trades';
  $handler->display->display_options['sorts']['field_trades_value']['field'] = 'field_trades_value';
  $handler->display->display_options['sorts']['field_trades_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_trades_value']['expose']['label'] = 'Total Trades';
  /* Sort criterion: Content: Winning trades (field_winning_trades) */
  $handler->display->display_options['sorts']['field_winning_trades_value']['id'] = 'field_winning_trades_value';
  $handler->display->display_options['sorts']['field_winning_trades_value']['table'] = 'field_data_field_winning_trades';
  $handler->display->display_options['sorts']['field_winning_trades_value']['field'] = 'field_winning_trades_value';
  $handler->display->display_options['sorts']['field_winning_trades_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_winning_trades_value']['expose']['label'] = 'Winning trades';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Sort criterion: Content: Profit (field_profit) */
  $handler->display->display_options['sorts']['field_profit_value']['id'] = 'field_profit_value';
  $handler->display->display_options['sorts']['field_profit_value']['table'] = 'field_data_field_profit';
  $handler->display->display_options['sorts']['field_profit_value']['field'] = 'field_profit_value';
  $handler->display->display_options['sorts']['field_profit_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_profit_value']['expose']['label'] = 'Pips';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'signal_provider' => 'signal_provider',
  );

  /* Display: Performance Page */
  $handler = $view->new_display('page', 'Performance Page', 'performance_page');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'performance-page';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'performance';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Performance';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'full';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['performance'] = $view;

  return $export;
}
