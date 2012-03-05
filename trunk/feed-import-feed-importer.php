<?php

	class FeedImporter
	{
		protected $config;
		public static $alreadyImported;
		public static $scheduledImports;
		public static $akas;
		
		public $rootJSON;
		
		public static $currentImporter;
	
		public function __construct ($config)
		{
			$this -> config						= $config;
			
			self::$currentImporter		= $this;
		}
		
		public function import ($customFeedOutput = null)
		{
		}
		
		public static function setAlreadyImported ($name, $value = true)
		{
			self::$alreadyImported [$name] = $value;
		}
		
		public static function getAlreadyImported ($name)
		{
			return @self::$alreadyImported [$name];
		}
		
		public static function schedule ($importer, $config)
		{
			self::$scheduledImports [] = array (
				'importer'				=> $importer,
				'importerConfig'	=> $config
			);
		}
		
		public static function doScheduledImports ()
		{
			if (!self::$scheduledImports)
				return;
			
			$importer = new SignalProvidersFeedImporter (array (
				'itemsPerPage'					=> 1,
				'pagesToImportPerCRON'	=> 1,
				'pagesToImportPerSite'	=> 1
			));
			
			
			while ($schedule = reset (self::$scheduledImports))
			{
				array_splice (self::$scheduledImports, 0, 1);
				
				$importer -> importCustomOutput ($schedule ['importerConfig'] ['FeedsPlusHTTPFetcher'] ['overrideOutput']);
			}
			
			self::doScheduledImports ();
		}
		
		public static function link ()
		{
		}
		
		public function finalize ()
		{
			db_query ("TRUNCATE z_cache_field");
						
			db_query ("
				REPLACE INTO z_field_data_field_known_as (entity_type, bundle, deleted, entity_id, revision_id, language, delta, field_known_as_nid)
				SELECT 'node', 'signal_provider', A.deleted, A.field_known_as_nid, A.revision_id, A.language, A.delta, A.entity_id
				FROM z_field_data_field_known_as A
				LEFT JOIN z_field_data_field_known_as B ON B.entity_id = A.field_known_as_nid
				WHERE B.entity_id IS NULL
			");
		}
	}
	
	FeedImporter::$alreadyImported	= array ();
	FeedImporter::$akas							= array ();
	FeedImporter::$scheduledImports	= array ();

?>