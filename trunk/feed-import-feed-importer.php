<?php

	class FeedImporter
	{
		protected $config;
		public static $alreadyImported;
		
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
		
		public function setAlreadyImported ($name, $value = true)
		{
			self::$alreadyImported [$name] = $value;
		}
		
		public function getAlreadyImported ($name)
		{
			return @self::$alreadyImported [$name];
		}
		
		public function finalize ()
		{
			db_query ("
				REPLACE INTO z_field_data_field_known_as (entity_type, bundle, deleted, entity_id, revision_id, language, delta, field_known_as_nid)
				SELECT 'node', 'signal_provider', A.deleted, A.field_known_as_nid, A.revision_id, A.language, A.delta, A.entity_id
				FROM z_field_data_field_known_as A
				LEFT JOIN z_field_data_field_known_as B ON B.entity_id = A.field_known_as_nid
				WHERE B.entity_id IS NULL
			");
		}
	}
	
	FeedImporter::$alreadyImported = array ();

?>