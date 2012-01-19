<?php

require_once dirname (__FILE__) . '/external/Curl.php';
require_once dirname (__FILE__) . '/../../contrib/feeds_jsonpath_parser/jsonpath-0.8.1.php';
require_once dirname (__FILE__) . '/external/JsonStore.php';

class FeedsPlusHTTPFetcherResult extends FeedsFetcherResult
{
	protected $config;
	static $receiversCache;

  public function __construct ($config)
  {
    parent::__construct ($config ['source']);
    
    $this -> config = $config;
  }
  
  public function getRaw ()
  {
  	$feed									= $this -> config ['feed'];
  	$url									= $this -> config ['source'];
  	$postVars							= $this -> config ['postVars'];
  	$postWholeContent			= $this -> config ['postWholeContent'];
  	$customReceivers			= $this -> config ['customReceivers'];
  	$parser								= $this -> config ['parser'];
  	
  	$curl			= new Curl ($url);
  	$curl -> setHeaders (array ('Content-type: application/json;charset=UTF-8'));
  	
  	if ($postVars)
  	{
  		if ($postWholeContent)
  			$curl -> setPostContent ($postVars);
  		else
  			$curl -> setPostAttributes (json_decode ($postVars));
  	}

  	$retrieved = $curl -> retrieve ();
  	
  	if ($customReceivers)
  	{
  		if ($parser == 'FeedsJSONPathParser')
  		{
  			$sourceJSON = json_decode ($retrieved, true);
  			
  			$field = new ReflectionProperty (get_class ($feed), 'config');
  			$field -> setAccessible (true);
  			$field = new ReflectionProperty ($parser, 'config');
  			$field -> setAccessible (true);
  			$field = new ReflectionProperty ('FeedsNodeProcessor', 'config');
  			$field -> setAccessible (true);
  			
  			$importerConfig = &$feed -> importer -> config;
  			
  			$parserContextPath	= &$importerConfig ['parser']    ['config'] ['context'];
  			$parserSources			= &$importerConfig ['parser']    ['config'] ['sources'];
  			$processorMappings	= &$importerConfig ['processor'] ['config'] ['mappings'];
  				
  			foreach ($customReceivers as $receiverName => $receiverConfig)
  			{
  				$receiverSource							= $receiverConfig ['source'];
  				$receiverSourceVar					= $receiverConfig ['sourceVar'];
  				$receiverPostVars						= $receiverConfig ['postVars'];
  				$receiverPostWholeContent		= $receiverConfig ['postWholeContent'];

  				$nodes = jsonPath ($sourceJSON, $parserContextPath);
  				 
  				foreach ($nodes as $nodeId => $node)
  				{
  					$receiverPostVars = preg_replace_callback (
  						'/#\{{1,1}([^\}]+)\}/',
  						function ($matches) use ($node, $receiverSourceVar) { return $node [$matches [1]]; },
  						$receiverPostVars
  					);
  					
	  				echo "* Trying to receive content for '" . $receiverName . "' from " . $receiverSource . "\n";
	  				
	  				$receiverCacheKey = $receiverSource . '_' . $nodeId;
	  				
	  				if (($cache = @self::$receiversCache [$receiverCacheKey]) !== null)
	  				{
	  					$receiverData = $cache;
	  					echo '-------------------------- USING CACHE ---------------------------';
	  				}
	  				else
	  				{
		  				$curl = new Curl ($receiverSource);
		  				$curl -> setHeaders (array ('Content-type: application/json'));
		  				if ($receiverPostVars)
		  					$receiverPostWholeContent ? $curl -> setPostContent ($receiverPostVars) : $curl -> setPostAttributes (json_decode ($receiverPostVars));
		  				
		  				self::$receiversCache [$receiverCacheKey] = $receiverData = $curl -> retrieve ();
	  				}
	  				
	  				echo $receiverSourceVar . "\n";
	  				
	  				$receiverDataJSON				= json_decode ($receiverData, true);
	  				$receiverSourceVarValue	= JsonStore::get ($receiverDataJSON, $receiverSourceVar);
	  				
	  				$JSONStorePath					= str_replace ('.*', '[' . $nodeId . '].0', $parserContextPath);
	  				
	  				JsonStore::add ($sourceJSON, $JSONStorePath, $receiverSourceVarValue, $receiverName);
  				}
	  				
  				
  			}
  			
  			return json_encode ($sourceJSON);
  		}
  	}
  	
  	return $retrieved;
  }
}

/**
 * Fetches data via HTTP.
 */
class FeedsPlusHTTPFetcher extends FeedsHTTPFetcher
{
	/**
	 * @overrides
	 */
	public function sourceForm ($source_config)
	{
		$form = array (
			'source' => array (
	      '#type'						=> 'textfield',
	      '#title'					=> t('URL'),
	      '#description'		=> t('Enter a feed URL.'),
	      '#default_value'	=> isset ($source_config ['source']) ? $source_config['source'] : '',
	      '#maxlength'			=> null,
	      '#required'				=> true
	     ),
	     
			'postWholeContent' => array (
	      '#type'						=> 'checkbox',
	      '#title'					=> t('POST the whole content'),
	      '#description'		=> t('If checked, following content will be treated as a single POST content. Elsewhere it will be treated as POST variables in the JSON format'),
	      '#default_value'	=> isset ($source_config ['postWholeContent']) ? $source_config ['postWholeContent'] : '',
	      '#maxlength'			=> null,
	      '#required'				=> false
			),
			
			'postVars' => array (
	      '#type'						=> 'textarea',
	      '#title'					=> t('POST content or POST variables'),
	      '#description'		=> t('POST content or POST variables in JSON format, e.g.: {userId:3,userName:"Sonic"}'),
	      '#default_value'	=> isset ($source_config ['postVars']) ? $source_config ['postVars'] : '',
	      '#maxlength'			=> null,
	      '#required'				=> true
			)
		);
		
		return $form;
	}
	
	
	/**
	 * @overrides
	 */
	public function fetch (FeedsSource $source)
	{
		$source_config = $source -> getConfigFor ($this);
		
		if ($this -> config['use_pubsubhubbub'] && ($raw = $this -> subscriber ($source -> feed_nid) -> receive ()))
			return new FeedsFetcherResult ($raw);
		
		return new FeedsPlusHTTPFetcherResult ($source_config);
	}
	

}

FeedsPlusHTTPFetcherResult::$receiversCache = array ();

?>