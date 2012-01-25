<?php
/**
 * @file
 * service_providers_signal_provider.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function service_providers_signal_provider_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'signal_providers';
  $feeds_importer->config = array(
    'name' => 'Signal Providers',
    'description' => 'Imports or updates available signal providers',
    'fetcher' => array(
      'plugin_key' => 'HTTP Fetcher (Feeds Plus)',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsJSONPathParser',
      'config' => array(
        'context' => '$.d.*',
        'sources' => array(
          'jsonpath_parser:0' => 'url',
          'jsonpath_parser:2' => 'name',
          'jsonpath_parser:3' => 'updatedOn',
          'jsonpath_parser:4' => 'updatedOn',
          'jsonpath_parser:5' => 'strategyName',
          'jsonpath_parser:6' => 'profit',
          'jsonpath_parser:7' => 'trades',
          'jsonpath_parser:8' => 'winningTrades',
          'jsonpath_parser:9' => 'avgPipsTrade',
          'jsonpath_parser:10' => 'avgTradeTime',
          'jsonpath_parser:11' => 'maxDrawDown',
          'jsonpath_parser:12' => 'maxOpenTrades',
          'jsonpath_parser:13' => 'worstTrade',
          'jsonpath_parser:14' => 'bestTrade',
          'jsonpath_parser:15' => 'followers',
          'jsonpath_parser:16' => 'hasLiveFollowers',
          'jsonpath_parser:17' => 'ranking',
          'jsonpath_parser:18' => 'runningWeeks',
          'jsonpath_parser:19' => 'necessaryMinEquity',
          'jsonpath_parser:20' => 'profileViewed',
          'jsonpath_parser:21' => 'balanceOfLiveAccounts',
          'jsonpath_parser:22' => 'accountType',
          'jsonpath_parser:23' => 'messages',
          'jsonpath_parser:24' => 'avgRating',
          'jsonpath_parser:25' => 'totalVotes',
          'jsonpath_parser:26' => 'id',
          'jsonpath_parser:27' => 'strategyName',
          'jsonpath_parser:28' => 'guid',
          'jsonpath_parser:29' => 'aka',
        ),
        'debug' => array(
          'options' => array(
            'context' => 'context',
            'jsonpath_parser:0' => 'jsonpath_parser:0',
            'jsonpath_parser:28' => 'jsonpath_parser:28',
            'jsonpath_parser:2' => 0,
            'jsonpath_parser:3' => 0,
            'jsonpath_parser:4' => 0,
            'jsonpath_parser:5' => 0,
            'jsonpath_parser:6' => 0,
            'jsonpath_parser:7' => 0,
            'jsonpath_parser:8' => 0,
            'jsonpath_parser:9' => 0,
            'jsonpath_parser:10' => 0,
            'jsonpath_parser:11' => 0,
            'jsonpath_parser:12' => 0,
            'jsonpath_parser:13' => 0,
            'jsonpath_parser:14' => 0,
            'jsonpath_parser:15' => 0,
            'jsonpath_parser:16' => 0,
            'jsonpath_parser:17' => 0,
            'jsonpath_parser:18' => 0,
            'jsonpath_parser:19' => 0,
            'jsonpath_parser:20' => 0,
            'jsonpath_parser:21' => 0,
            'jsonpath_parser:22' => 0,
            'jsonpath_parser:23' => 0,
            'jsonpath_parser:24' => 0,
            'jsonpath_parser:25' => 0,
            'jsonpath_parser:26' => 0,
            'jsonpath_parser:27' => 0,
            'jsonpath_parser:29' => 0,
          ),
        ),
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'signal_provider',
        'expire' => '10800',
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'jsonpath_parser:0',
            'target' => 'url',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'jsonpath_parser:2',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'jsonpath_parser:3',
            'target' => 'field_updated_on:start',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'jsonpath_parser:4',
            'target' => 'field_updated_on:end',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'jsonpath_parser:5',
            'target' => 'body',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'jsonpath_parser:6',
            'target' => 'field_profit',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'jsonpath_parser:7',
            'target' => 'field_trades',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'jsonpath_parser:8',
            'target' => 'field_winning_trades',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'jsonpath_parser:9',
            'target' => 'field_avg_pips_trade',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'jsonpath_parser:10',
            'target' => 'field_avg_trade_time',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'jsonpath_parser:11',
            'target' => 'field_max_drawdown',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'jsonpath_parser:12',
            'target' => 'field_max_open_trades',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'jsonpath_parser:13',
            'target' => 'field_worst_trade',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'jsonpath_parser:14',
            'target' => 'field_best_trade',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'jsonpath_parser:15',
            'target' => 'field_followers',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'jsonpath_parser:16',
            'target' => 'field_has_live_followers',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'jsonpath_parser:17',
            'target' => 'field_ranking',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'jsonpath_parser:18',
            'target' => 'field_running_weeks',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'jsonpath_parser:19',
            'target' => 'field_necessary_minimum_equity',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'jsonpath_parser:20',
            'target' => 'field_profile_viewed',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'jsonpath_parser:21',
            'target' => 'field_balance_of_live_accounts',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'jsonpath_parser:22',
            'target' => 'field_account_type',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'jsonpath_parser:23',
            'target' => 'field_messages',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'jsonpath_parser:24',
            'target' => 'field_avg_rating',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'jsonpath_parser:25',
            'target' => 'field_total_votes',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'jsonpath_parser:26',
            'target' => 'field_sp_id',
            'unique' => FALSE,
          ),
          26 => array(
            'source' => 'jsonpath_parser:27',
            'target' => 'field_strategy_name',
            'unique' => FALSE,
          ),
          27 => array(
            'source' => 'jsonpath_parser:28',
            'target' => 'guid',
            'unique' => 1,
          ),
          28 => array(
            'source' => 'jsonpath_parser:29',
            'target' => 'field_known_as:guid',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
      ),
    ),
    'content_type' => 'signal_provider',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 0,
    'process_in_background' => 0,
  );
  $export['signal_providers'] = $feeds_importer;

  return $export;
}
