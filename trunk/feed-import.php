<?php

	if (!(php_sapi_name () == 'cli' || empty ($_SERVER['REMOTE_ADDR'])))
		die ('<div class="padding: 20px; font-family: Helvetica, Arial">Sorry, <b>FeedsImporter</b> could be ran from the command line or CRON task only<br />Usage: <i>drush php-script feed-import.php</i></div>');

	set_time_limit (60 * 30); // 30 minutes

	// We have to block execution of this task until task is done.

	echo "* ZulumaxImporter: Locking importer task\n";

	$lockFilePath								= sys_get_temp_dir () . 'zulumax.lock';
	$currentSPPagePath					= sys_get_temp_dir () . 'zulumax.sp-page';
	$numSPItemsPerPage					= 1;
	$numSPPagesToImportPerCRON	= 1;
	$numSPPagesToImportPerSite	= $numSPPagesToImportPerCRON * 1;

	$handle											= fopen ($lockFilePath, "w");
	$locked											= false;

	if (!$handle)
		die ("* ZulumaxImporter: Couldn't open lock file $lockFilePath\n");
	
	// Locking task
	if (!flock ($handle, LOCK_EX))
	{
		echo "* ZulumaxImporter: Couldn't acquire the lock for $lockFilePath\n";
		
		if (strtoupper(substr(PHP_OS, 0, 3)) !== 'WIN')
			exit;
	}
	
	if ($locked)
	{
		// Writting current time to the lock file content
		ftruncate ($handle, 0);
		fwrite ($fp, time ());
	}

	
	// Import should be done partially on each CRON call, so we have to save the current crawling position for future use.
	$currentSPPage = (int)@file_get_contents ($currentSPPagePath);
	
	if ($currentSPPage >= $numSPPagesToImportPerSite)
		$currentSPPage = 0;

	for ($page = 0; $page < $numSPPagesToImportPerCRON; $page++)
	{
		echo '  ZulumaxImporter: Importing SignalProvider page ' . ($currentSPPage + $page + 1) . ' up to ' . ($currentSPPage + $numSPPagesToImportPerCRON) . " from the " . ($numSPPagesToImportPerSite) . " pages allowed to import\n";
		
		$feed = feeds_source ('signal_providers');
		
		$feed -> addConfig (array (
			'FeedsPlusHTTPFetcher' 		=> array (
				'feed'									=> $feed,
				'context'								=> array (),
				'source'								=> 'http://zulutrade.com/WebServices/Performance.asmx/SearchProviders',
				'postVars'							=> '{"searchFilter":{"SortExpression":0,"SortDirection":0,"Page":' . $currentSPPage . ',"PageSize":' . $numSPItemsPerPage . ',"ProviderName":"","CountryCode":"","IsLive":false,"WinningTrades":false,"TradingWeeks":false,"Top100":false,"ApprovedPhoto":false,"RecentTrading":false,"Rated":false,"LiveFollowers":false,"EconomicEvents":false,"HasVideos":false,"IsBookmarked":false,"NotTradingExotics":false,"PipsFrom":"","PipsTo":"","TradesFrom":"","TradesTo":"","AvgPipsFrom":null,"AvgPipsTo":null,"WinningTradesFrom":null,"WinningTradesTo":null,"WeeksFrom":null,"WeeksTo":null,"MaxDDFrom":null,"MaxDDTo":null,"MaxDDPipsFrom":null,"MaxDDPipsTo":null,"CorrelationFrom":null,"CorrelationTo":null,"FollowersFrom":null,"FollowersTo":null,"MaxOpenTradesFrom":null,"MaxOpenTradesTo":null,"LowestPipValueFrom":null,"LowestPipValueTo":null,"BestTradeFrom":null,"BestTradeTo":null,"AvgTradeTimeFrom":null,"AvgTradeTimeTo":null,"AverageSlippageFrom":null,"AverageSlippageTo":null,"Timeframe":null,"ProfitableAccount":null,"LosingAccount":null,"Relation":null,"CurrencyPairs":null,"AffiliateID":-1}}',
				'postWholeContent'			=> true,
				'parser'								=> 'FeedsJSONPathParser',
				'customReceivers' 			=> array (
					'strategyName'				=> array (
						'source'						=> 'http://zulutrade.com/WebServices/Performance.asmx/GetProviderStrategy',
						'sourceVar'					=> 'd',
						'sourceParser'			=> 'FeedsJSONPathParser',
						'postVars'					=> '{"providerId":#{id}}',
						'postWholeContent'	=> true
					)
				)
			)
		));
		
		while (FEEDS_BATCH_COMPLETE != $feed -> import ())
		{
			sleep (1);
		}
	}
	
	file_put_contents ($currentSPPagePath, $currentSPPage + $page);
	
	
	echo "* ZulumaxImporter: Unlocking importer task\n";
	
	if ($locked)
	// Unlocking task
		flock ($handle, LOCK_UN);
	
	fclose ($handle);
	

?>