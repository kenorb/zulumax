<?php

require_once dirname (__FILE__) . '/external/Curl.php';
require_once dirname (__FILE__) . '/../../contrib/feeds_jsonpath_parser/jsonpath-0.8.1.php';
require_once dirname (__FILE__) . '/external/JsonStore.php';

class FeedsPlusFeedsSource extends FeedsSource
{
	protected $nid;
	protected $alreadySaved;
	
	public function getImporterConfig ()
	{
		return $this -> importer -> getConfig ();
	}

	public function getResult ()
	{
		return $this -> config ['FeedsPlusHTTPFetcher'] ['importer'] -> rootJSON;
	}
	
	public function addImporterConfig ($config)
	{
		$this -> importer -> addConfig ($config);
	}
	
	public function setNid ($nid)
	{
		$this -> nid = $nid;
	}
	public function getNid ()
	{
		return $this -> nid;
	}
	
}

class FeedsPlusHTTPFetcherResult extends FeedsFetcherResult
{
	protected $config;
	static $receiversCache;
	
	const Content_Text							= 0;
	const Content_FileDownload			= 1;
	
	const ReceiverParser_None				= 0;
	const ReceiverParser_HTML				= 1;
	const ReceiverParser_HTML_Regex	= 2;
	const ReceiverParser_JSON				= 3;
	
	static public $temporaryNode;
	private $temporary;

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
  	$importer							= @$this -> config ['importer'];
  	$customFeedOutput			= @$this -> config ['overrideOutput'];
  	
  	$curl = new Curl ($url);
  	$curl -> setHeaders (array ('Content-type: application/json;charset=UTF-8'));

  	if ($customFeedOutput)
  		$retrieved = $customFeedOutput;
  	else
  	{
	  	if ($postVars)
	  	{
	  		if ($postWholeContent)
	  			$curl -> setPostContent ($postVars);
	  		else
	  			$curl -> setPostAttributes (json_decode ($postVars));
	  	}
	
	  	$retrieved = $curl -> retrieve ();
  	}
  	
  	if ($customReceivers)
  	{
  		$importerConfig			= $feed -> getImporterConfig ();
  		$parserContextPath	= $importerConfig ['parser']    ['config'] ['context'];
  		
  		if ($parser == 'JSON')
  		{
  			$sourceJSON = json_decode ($retrieved, true);
  			
  			$nodes = jsonPath ($sourceJSON, $parserContextPath);

  			$nodes = array ($nodes [0]);

  			foreach ($nodes as $nodeId => $node)
  				JsonStore::add ($sourceJSON, '$.d[' . $nodeId . '].0', md5 ($node ['id']), 'guid');
  			
  			foreach ($customReceivers as $receiverName => $receiverConfig)
  			{
  				$receiverSource							= @$receiverConfig ['source'];
  				$receiverSourceContent			= @$receiverConfig ['sourceContent'];
  				$receiverSourceVar					= @$receiverConfig ['sourceVar'];
  				$receiverSourceParser				= @$receiverConfig ['sourceParser'];
  				$receiverPostVars						= @$receiverConfig ['postVars'];
  				$receiverSourceMatcher			= @$receiverConfig ['sourceMatcher'];
  				$receiverPostWholeContent		= @$receiverConfig ['postWholeContent'];
  				$sourceVarCallback					= @$receiverConfig ['sourceVarCallback'];
  				$receiverValueOverride			= @$receiverConfig ['value'];
  				
  				if (!$receiverSourceContent)
  					$receiverSourceContent = self::Content_Text;
  				
  				foreach ($nodes as $nodeId => $node)
  				{
  					$JSONStorePath					= str_replace ('.*', '[' . $nodeId . '].0', $parserContextPath);
  					
  					self::$temporaryNode = $node;
  					
  					if ($receiverPostVars)
  						$receiverPostVarsProcessed = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
	  						create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  							$receiverPostVars
  						);
  					
  					if ($receiverSource)
	  					$receiverSourceProcessed = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
  							create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  							$receiverSource
  						);
  					
  					if (isset ($receiverValueOverride))
							$receiverValueOverride = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
  							create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  							$receiverValueOverride
  						);

  					switch ($receiverSourceContent)
  					{
  						case self::Content_Text:
  					
		  					if (!$receiverValueOverride)
		  					{
				  				echo "* Trying to receive content for '" . $receiverName . "' from " . $receiverSourceProcessed . "\n";
			
				  				$receiverCacheKey = $receiverSourceProcessed . '_' . $nodeId . ($receiverPostVars ? ('_' . $receiverPostVars) : '');
				  				
				  				if (($cache = @self::$receiversCache [$receiverCacheKey]) !== null)
				  					$receiverData = $cache;
				  				else
				  				{
					  				$curl = new Curl ($receiverSourceProcessed);
					  				$curl -> setHeaders (array ('Content-type: application/json'));
					  				
					  				if ($receiverPostVarsProcessed)
					  					$receiverPostWholeContent ? $curl -> setPostContent ($receiverPostVarsProcessed) : $curl -> setPostAttributes (json_decode ($receiverPostVarsProcessed));
					  				
					  				self::$receiversCache [$receiverCacheKey] = $receiverData = $curl -> retrieve ();
				  				}
				  				
				  				if ($receiverSourceParser == self::ReceiverParser_HTML_Regex)
				  				{
				  					preg_match ($receiverSourceVar, $receiverData, $matches);
				  					
				  					if ($receiverSourceMatcher)
				  						$receiverSourceVarValue = $receiverSourceMatcher ($matches, $this -> config, $feed, $node);
				  					else
				  						$receiverSourceVarValue = $matches [1];
				  				}
				  				else
				  				if ($receiverSourceParser == self::ReceiverParser_JSON)
					  				$receiverSourceVarValue	= JsonStore::get (json_decode ($receiverData, true), $receiverSourceVar);
					  			
				  				
				  				if (is_string ($receiverSourceVarValue))
				  					$receiverSourceVarValue = trim ($receiverSourceVarValue);
				  				
		
				  				if ($sourceVarCallback)
				  					$sourceVarCallback ($receiverSourceVarValue);
		  					}
		  					else
		  						$receiverSourceVarValue = $receiverValueOverride;
		  					
		  					break;
		  				
  						case self::Content_FileDownload:
  							
  							$receiverDownloadTarget					= @$receiverConfig ['downloadTarget'];

  							$receiverDownloadTarget = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
  								create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  								$receiverDownloadTarget
  							);
  								
  							$receiverSource = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
  								create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  								$receiverSource
  							);
  							
  							global $conf, $base_path;
  							
  							$fileHandle		= fopen ($conf ['file_public_path'] . '/' . $receiverDownloadTarget, 'w+');
  							
  							$curl					= curl_init ($receiverSource);
  							
  							curl_setopt	($curl, CURLOPT_TIMEOUT,				50);
  							curl_setopt	($curl, CURLOPT_FILE,						$fileHandle);
  							curl_setopt	($curl, CURLOPT_FOLLOWLOCATION, true);
  							curl_setopt ($curl, CURLOPT_REFERER,				'http://zulutrade.com/Performance.aspx');
  							curl_exec		($curl);
  							curl_close	($curl);
  							
  							fclose			($fileHandle);
  							
  							$receiverSourceVarValue = 'public://' . $receiverDownloadTarget;

  							break;
  					}
	  				
  					
	  				JsonStore::add ($sourceJSON, $JSONStorePath, $receiverSourceVarValue, $receiverName);
  				}
	 			}
	 			
	 			$sourceEncoded = json_encode ($sourceJSON);
	 			
	 			if ($importer)
	 			{
	 				$importer -> rootJSON	= JsonStore::get ($sourceJSON, $parserContextPath);
	 			}
	 			
  			return $sourceEncoded;
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