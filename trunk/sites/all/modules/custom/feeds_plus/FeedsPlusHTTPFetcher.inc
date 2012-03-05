<?php

require_once dirname (__FILE__) . '/external/Curl.php';
require_once dirname (__FILE__) . '/../../contrib/feeds_jsonpath_parser/jsonpath-0.8.1.php';
require_once dirname (__FILE__) . '/external/JsonStore.php';

class FeedsPlusFeedsSource extends FeedsSource
{
	protected $nid;
	protected $alreadySaved;
	protected $fetcherResultCopy;
	
	public function __construct ($a, $b)
	{
		parent::__construct ($a, $b);
	}
	
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
  	
  	if (!$customFeedOutput && $url == 'http://zulutrade.com/WebServices/Performance.asmx/SearchProviders' && false)
  	//$retrieved = '{"d":[{"__type":"Z.P","id":20558,"bid":228145,"n":"FxTraderX","n2":"FxTraderX","cc":"UA","cn":"Ukraine","bl":"image/common/brokers/AAAFx-small.png","e":0,"l":2,"r":0,"f":0,"b":0,"uid":-1,"c":0,"ar":3,"ra":4,"pp":"12.2K","t":1745,"ap":7,"w":58,"at":"1d","tw":85,"dc":"10","dp":"1.3K","fo":639,"la":"8 godziny","lo":0,"s":"Use .3 mini lots to every 1000 in capital with ...","mot":27,"lr":"You\u0027re in 2nd spot for a very good reason - you\u0027ve decreased your trades which is paying off - it\u0027s about profit and not losing - nice and steady every time wins the race - very well done keep it up","lru":"AAA648025F","af":230546.16,"cp":26.400000000000002,"roio":340.1,"roia":208,"ror":322.1,"nme":0}]}';
  		$retrieved = '{"d":[]}';
  	else
  	{
	
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
  	}
  	
  	if ($customReceivers)
  	{
  		$importerConfig			= $feed -> getImporterConfig ();
  		$parserContextPath	= $importerConfig ['parser']    ['config'] ['context'];
  		
  		if ($parser == 'JSON')
  		{
  			$sourceJSON = json_decode ($retrieved, true);
  			
  			$nodes = jsonPath ($sourceJSON, $parserContextPath);
  			
  			if (!is_array ($nodes))
  				$nodes = array ();
  				
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
  				$skip												= @$receiverConfig ['skip'];
  				 
  				if ($skip)
  					continue;
  				
  				if (!$receiverSourceContent)
  					$receiverSourceContent = self::Content_Text;
  				
  				foreach ($nodes as $nodeId => $node)
  				{
  					$JSONStorePath					= str_replace ('.*', '[' . $nodeId . '].0', $parserContextPath);
  					
  					self::$temporaryNode = $node;
  					
  					$receiverPostVarsProcessed			= null;
  					$receiverSourceProcessed				= null;
  					$receiverValueOverrideProcessed	= null;
  					
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
							$receiverValueOverrideProcessed = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
  							create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  							$receiverValueOverride
  						);

  					switch ($receiverSourceContent)
  					{
  						case self::Content_Text:
  					
		  					if (!$receiverValueOverrideProcessed)
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
		  						$receiverSourceVarValue = $receiverValueOverrideProcessed;
		  					
		  					break;
		  				
  						case self::Content_FileDownload:
  							
  							$receiverDownloadTarget					= @$receiverConfig ['downloadTarget'];

  							$receiverDownloadTarget = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
  								create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  								$receiverDownloadTarget
  							);
  								
  							$receiverSourceFinal = preg_replace_callback ('/#\{{1,1}([^\}]+)\}/',
  								create_function ('$matches', 'return FeedsPlusHTTPFetcherResult::$temporaryNode [$matches [1]];'),
  								$receiverSource
  							);
  							
  							global $conf, $base_path;
  							
  							$fileHandle		= fopen ($conf ['file_public_path'] . '/' . $receiverDownloadTarget, 'w+');
  							
  							echo $receiverSourceFinal . "\n";
  							
  							$curl					= curl_init ($receiverSourceFinal);
  							
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
	      '#required'				=> false
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
	      '#required'				=> false
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