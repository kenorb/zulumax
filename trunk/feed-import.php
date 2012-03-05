<?php

	require_once 'feed-import-signal-providers.php';

	if (!(php_sapi_name () == 'cli' || empty ($_SERVER['REMOTE_ADDR'])))
		die ('<div class="padding: 20px; font-family: Helvetica, Arial">Sorry, <b>FeedsImporter</b> could be ran from the command line or CRON task only<br />Usage: <i>drush php-script feed-import.php</i></div>');

	set_time_limit (60 * 30); // 30 minutes

	// We have to block execution of this task until task is done.

	echo "* ZulumaxImporter: Locking importer task\n";

	variable_set ('feeds_source_class', 'FeedsPlusFeedsSource');
	
	$lockFilePath								= sys_get_temp_dir () . 'zulumax.lock';
	
	$importer = new SignalProvidersFeedImporter (array (
		'itemsPerPage'					=> 20,
		'pagesToImportPerCRON'	=> 10,
		'pagesToImportPerSite'	=> 1000000
	));
	
	
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

	
	$importer -> import ();
	$importer -> link ();
	$importer -> finalize ();
	
	
	
	echo "* ZulumaxImporter: Unlocking importer task\n";
	
	if ($locked)
	// Unlocking task
		flock ($handle, LOCK_UN);
	
	fclose ($handle);
	

?>