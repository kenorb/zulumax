<?php

	require_once 'feed-import-feed-importer.php';
	
	ini_set ('xdebug.max_nesting_level', 2000);

	class SignalProvidersFeedImporter extends FeedImporter
	{
		protected $receivers;
		
		public static function addAka ($left, $right)
		{
			self::$akas [$left] [] = $right;
		}
		
		public static function link ()
		{
			foreach (self::$akas as $left => $rights)
			{
				foreach ($rights as $right)
				{
					echo $left . " links with " . $right . "\n";
					
					$leftId		= db_query ("SELECT entity_id FROM {feeds_item} WHERE guid = '$left'  LIMIT 1") -> fetchField ();
					$rightId	= db_query ("SELECT entity_id FROM {feeds_item} WHERE guid = '$right' LIMIT 1") -> fetchField ();

					db_query ($query = "
						REPLACE INTO {field_data_field_known_as} (entity_type, bundle, deleted, entity_id, revision_id, language, delta, field_known_as_nid)
						SELECT 'node', 'signal_provider', 0, $leftId, 0, 'und', $rightId, $rightId
					");
				}
			}
		}
		
		public function __construct ($config)
		{
			parent::__construct ($config);
			
			$this -> receivers = array (
			
				'-id'									=> array (
					'source'						=> 'http://127.0.0.1/',
					'sourceVar'					=> '/^NOTHING$/',
					'sourceMatcher'			=> create_function ('&$var, $config, $feed, &$node', 'FeedImporter::setAlreadyImported ($node ["id"], true);'),
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex
				),
				
				'aka'									=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '%ctl00_box1_TableRowDuplicateAccounts[^>]+>(.*?)</td>%si',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceMatcher'			=> create_function ('&$var, $config, $feed, &$node', '

							preg_match_all ("/\\?pid=([0-9]+)/i", $var [1], $matches);
							
							if (@$matches [1])
							{
								foreach ($matches [1] as $id)
								{
									$config ["importer"] -> addAka ($node ["id"], $id);
			
									if (!FeedImporter::getAlreadyImported ($id))
									{
										echo "Not yet imported $id, adding to the queue\n";
										
										FeedImporter::setAlreadyImported ($id, true);
		
										$config ["importer"] -> importCustomInput ("{\"d\":[{\"id\":" . $id . "}]}");
									}
								}
							}
							
							return array ();
						')
				),
				
				'guid'								=> array (
					'value'							=> '#{id}'
				),
			
				'tradingHistoryCSV'		=> array (
					'source'						=> 'http://zulutrade.com/Export.ashx?d=providertrades&f=csv&id=#{id}&c=&df=1984-09-09&dt=2013-01-26',
					'sourceContent'			=> FeedsPlusHTTPFetcherResult::Content_FileDownload,
					'downloadTarget'		=> 'CSV-SP/#{id}.csv'
				),
				
				'url'									=> array (
					'value'							=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
				),
				
				'name'								=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '%class="name">(.*?)</span>%si',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = trim (strip_tags ($var));')
				),
				
				'strategyName'				=> array (
					'source'						=> 'http://zulutrade.com/WebServices/Performance.asmx/GetProviderStrategy',
					'sourceVar'					=> 'd',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_JSON,
					'postVars'					=> '{"providerId":#{id}}',
					'postWholeContent'	=> true
				),
			
				'profit'							=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/"ctl00_box1_lbPips"[^>]+>([^ ]+)/',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				'trades'							=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Trades[^"]+[^>]+>([^<]+)</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				'winningTrades'				=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Winning trades[^"]+[^>]+>[^0-9]+([0-9]+)/',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex
				),
				
				'avgPipsTrade'				=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Average pips\/trade[^"]+[^>]+>([^<]+)</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				// Float(Hours)
				'avgTradeTime'				=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Average trade time[^"]+[^>]+>([^<]+)</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '
						$var = str_replace (",", "", $var);
						
						if (strpos ($var, "hours") !== false)
							$var = (float)(substr ($var, 0, strlen ($var) - 5));
						else
						if (strpos ($var, "days") !== false)
							$var = (float)(substr ($var, 0, strlen ($var) - 4) * 24);
						else
						if (strpos ($var, "minutes") !== false)
							$var = (float)(substr ($var, 0, strlen ($var) - 7) / 60);
						else
							$var = (float)$var;
					')
				),
	
				// Int
				'maxDrawDown'					=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_LabelMaxDrawdown"[^"]+"[^"]+"[^>]+>([^%]+)%/m',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
	
				'maxOpenTrades'				=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_LabelMaxOpenTrades"[^"]+"[^"]+"[^>]+>([^<]+)</m',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				'worstTrade'					=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_LabelMaxLow[^>]+>([^p]+)pips</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				'bestTrade'						=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_LabelBestTrade[^>]+>([^p]+)pips</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
	
				'followers'						=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Followers[^"]+[^>]+>([^<]+)</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				'hasLiveFollowers'		=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Has live followers[^"]+[^>]+>([^<]+)</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = $var == "yes" ? 1 : 0;')
				),
				
				// Int
				'ranking'							=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_LabelRanking[^>]+>[^0-9]*([0-9]+)/m',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
//					'sourceMatcher'	=> create_function ('$var', 'var_dump($var);exit;')
				),
	
				'runningWeeks'				=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Running weeks[^"]+[^>]+>([^<]+)</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				// Int
				'necessaryMinEquity'	=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_LabelNME"[^>]+>\$([^<]+)</m',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
				
				'profileViewed'				=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Viewed[^"]+[^>]+>([^t]+)times[^<]+</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = str_replace (",", "", $var);')
				),
	
				// Date
				'updatedOn'						=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/Updated on[^"]+[^>]+>([^<]+)</',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex,
					'sourceVarCallback'	=> create_function ('&$var', '$var = date ("m/d/Y m:h", strtotime ($var));')
				),
				
				'profile'							=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_lbAvatar[^>]+>[^>]+>([^<]+)</m',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex
				),
				
				'balanceOfLiveAccounts' => array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_LabelAmountFollowing[^>]+>([^<]+)</m',
					'sourceVarCallback'	=> create_function ('&$var', '$var = (int)str_replace (",", "", substr ($var, 1));'),
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex
				),
				
				'accountType'					=> array (
					'source'						=> 'http://zulutrade.com/TradeHistoryIndividual.aspx?pid=#{id}&Lang=en',
					'sourceVar'					=> '/ctl00_box1_(DivRealMoneyBlue|DivRealMoney)/',
					'sourceVarCallback'	=> create_function ('&$var', '
						switch ($var)
						{
							case "DivRealMoney":			$var = "live";				break;
							case "DivRealMoneyBlue":	$var = "following";		break;
							default:									$var = "demo";
						}
					'),
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_HTML_Regex
				),
				
				'avgRating'						=> array (
					'source'						=> 'http://zulutrade.com/WebServices/ProviderRating.asmx/GetAverageRatings',
					'postVars'					=> '{"providerID":#{id}}',
					'postWholeContent'	=> true,
					'sourceVar'					=> 'd.ta',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_JSON,
					'sourceMatcher'			=> create_function ('$var', '')
				),
				
				'totalVotes'					=> array (
					'source'						=> 'http://zulutrade.com/WebServices/ProviderRating.asmx/GetAverageRatings',
					'postVars'					=> '{"providerID":#{id}}',
					'postWholeContent'	=> true,
					'sourceVar'					=> 'd.tr',
					'sourceParser'			=> FeedsPlusHTTPFetcherResult::ReceiverParser_JSON
				)

			);
		}

		public function importCustomInput ($customFeedOutput)
		{
			FeedImporter::schedule ('signal_providers', array (
					'FeedsPlusHTTPFetcher' 		=> array (
						'context'								=> array (),
						'source'								=> 'http://zulutrade.com/WebServices/Performance.asmx/SearchProviders',
						'postVars'							=> '{"searchFilter":{"SortExpression":0,"SortDirection":0,"Page":' . $currentSPPage . ',"PageSize":' . $this -> config ['itemsPerPage'] . ',"ProviderName":"","CountryCode":"","IsLive":false,"WinningTrades":false,"TradingWeeks":false,"Top100":false,"ApprovedPhoto":false,"RecentTrading":false,"Rated":false,"LiveFollowers":false,"EconomicEvents":false,"HasVideos":false,"IsBookmarked":false,"NotTradingExotics":false,"PipsFrom":"","PipsTo":"","TradesFrom":"","TradesTo":"","AvgPipsFrom":null,"AvgPipsTo":null,"WinningTradesFrom":null,"WinningTradesTo":null,"WeeksFrom":null,"WeeksTo":null,"MaxDDFrom":null,"MaxDDTo":null,"MaxDDPipsFrom":null,"MaxDDPipsTo":null,"CorrelationFrom":null,"CorrelationTo":null,"FollowersFrom":null,"FollowersTo":null,"MaxOpenTradesFrom":null,"MaxOpenTradesTo":null,"LowestPipValueFrom":null,"LowestPipValueTo":null,"BestTradeFrom":null,"BestTradeTo":null,"AvgTradeTimeFrom":null,"AvgTradeTimeTo":null,"AverageSlippageFrom":null,"AverageSlippageTo":null,"Timeframe":null,"ProfitableAccount":null,"LosingAccount":null,"Relation":null,"CurrencyPairs":null,"AffiliateID":-1}}',
						'postWholeContent'			=> true,
						'parser'								=> 'JSON',
						'overrideOutput'				=> $customFeedOutput,
						'importer'							=> $this,
						'customReceivers' 			=> $this -> receivers,
						'overrideOutput'				=> $customFeedOutput
					)
				));
		}

		public function importCustomOutput ($customFeedOutput = null)
		{
			$feed = feeds_source ('signal_providers');
						
			$feed -> addImporterConfig (array ('content_type' => 'signal_provider'));
						
			$feed -> addConfig (array (
				'FeedsPlusHTTPFetcher' 		=> array (
					'feed'									=> $feed,
					'context'								=> array (),
					'source'								=> 'http://zulutrade.com/WebServices/Performance.asmx/SearchProviders',
					'postVars'							=> '{"searchFilter":{"SortExpression":0,"SortDirection":0,"Page":' . $currentSPPage . ',"PageSize":' . $this -> config ['itemsPerPage'] . ',"ProviderName":"","CountryCode":"","IsLive":false,"WinningTrades":false,"TradingWeeks":false,"Top100":false,"ApprovedPhoto":false,"RecentTrading":false,"Rated":false,"LiveFollowers":false,"EconomicEvents":false,"HasVideos":false,"IsBookmarked":false,"NotTradingExotics":false,"PipsFrom":"","PipsTo":"","TradesFrom":"","TradesTo":"","AvgPipsFrom":null,"AvgPipsTo":null,"WinningTradesFrom":null,"WinningTradesTo":null,"WeeksFrom":null,"WeeksTo":null,"MaxDDFrom":null,"MaxDDTo":null,"MaxDDPipsFrom":null,"MaxDDPipsTo":null,"CorrelationFrom":null,"CorrelationTo":null,"FollowersFrom":null,"FollowersTo":null,"MaxOpenTradesFrom":null,"MaxOpenTradesTo":null,"LowestPipValueFrom":null,"LowestPipValueTo":null,"BestTradeFrom":null,"BestTradeTo":null,"AvgTradeTimeFrom":null,"AvgTradeTimeTo":null,"AverageSlippageFrom":null,"AverageSlippageTo":null,"Timeframe":null,"ProfitableAccount":null,"LosingAccount":null,"Relation":null,"CurrencyPairs":null,"AffiliateID":-1}}',
					'postWholeContent'			=> true,
					'parser'								=> 'JSON',
					'overrideOutput'				=> $customFeedOutput,
					'importer'							=> $this,
					'customReceivers' 			=> $this -> receivers
				)
			));
		
			while ($feed -> import () != FEEDS_BATCH_COMPLETE);
		}
		
		public function import ($customFeedOutput = null)
		{
			$currentSPPagePath = sys_get_temp_dir () . 'zulumax.sp-page';
			
			// Import should be done partially on each CRON call, so we have to save the current crawling position for future use.
			$currentSPPage = (int)@file_get_contents ($currentSPPagePath);
			
			if ($currentSPPage >= $this -> config ['pagesToImportPerSite'])
				$currentSPPage = 0;
		
			for ($page = 0; $page < $this -> config ['pagesToImportPerCRON']; $page++)
			{
				echo '  ZulumaxImporter: Importing SignalProvider page ' . ($currentSPPage + $page + 1) . ' up to ' . ($currentSPPage + $this -> config ['pagesToImportPerCRON']) . " from the " . ($this -> config ['pagesToImportPerSite']) . " pages allowed to import\n";
				
				$feed = feeds_source ('signal_providers');
				
				$feed -> addImporterConfig (array ('content_type' => 'signal_provider'));
				
				$feed -> addConfig (array (
					'FeedsPlusHTTPFetcher' 		=> array (
						'feed'									=> $feed,
						'context'								=> array (),
						'source'								=> 'http://zulutrade.com/WebServices/Performance.asmx/SearchProviders',
						'postVars'							=> '{"searchFilter":{"SortExpression":0,"SortDirection":0,"Page":' . $currentSPPage . ',"PageSize":' . $this -> config ['itemsPerPage'] . ',"ProviderName":"","CountryCode":"","IsLive":false,"WinningTrades":false,"TradingWeeks":false,"Top100":false,"ApprovedPhoto":false,"RecentTrading":false,"Rated":false,"LiveFollowers":false,"EconomicEvents":false,"HasVideos":false,"IsBookmarked":false,"NotTradingExotics":false,"PipsFrom":"","PipsTo":"","TradesFrom":"","TradesTo":"","AvgPipsFrom":null,"AvgPipsTo":null,"WinningTradesFrom":null,"WinningTradesTo":null,"WeeksFrom":null,"WeeksTo":null,"MaxDDFrom":null,"MaxDDTo":null,"MaxDDPipsFrom":null,"MaxDDPipsTo":null,"CorrelationFrom":null,"CorrelationTo":null,"FollowersFrom":null,"FollowersTo":null,"MaxOpenTradesFrom":null,"MaxOpenTradesTo":null,"LowestPipValueFrom":null,"LowestPipValueTo":null,"BestTradeFrom":null,"BestTradeTo":null,"AvgTradeTimeFrom":null,"AvgTradeTimeTo":null,"AverageSlippageFrom":null,"AverageSlippageTo":null,"Timeframe":null,"ProfitableAccount":null,"LosingAccount":null,"Relation":null,"CurrencyPairs":null,"AffiliateID":-1}}',
						'postWholeContent'			=> true,
						'parser'								=> 'JSON',
						'overrideOutput'				=> $customFeedOutput,
						'importer'							=> $this,
						'customReceivers' 			=> $this -> receivers
					)
				));
				
				while ($feed -> import () != FEEDS_BATCH_COMPLETE);
				
				if (!$feed -> getResult ())
				{
					echo "* ZulumaxImporter: There was no more nodes to import. Next import will start from the first page\n";
					
					$currentSPPage = $page = 0;
					
					break;
				}
				
				FeedImporter::doScheduledImports ();
			}
			
			file_put_contents ($currentSPPagePath, $currentSPPage + $page);
			
		}
	
	}

?>