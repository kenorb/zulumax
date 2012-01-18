<?php

require_once dirname (__FILE__) . '/external/Curl.php';

class FeedsPlusHTTPFetcherResult extends FeedsFetcherResult
{
	protected $config;

  public function __construct ($config)
  {
    parent::__construct ($config ['source']);
    
    $this -> config = $config;
  }

  public function getRaw ()
  {
  	$url								= $this -> config ['source'];
  	$postVars						= $this -> config ['postVars'];
  	$postWholeContent		= $this -> config ['postWholeContent'];
  	
  	$curl			= new Curl ($url);
  	
  	$curl -> setHeaders (array ('Content-type: application/json'));
  	
  	if ($postVars)
  	{
  		if ($postWholeContent)
  			$curl -> setPostContent ($postVars);
  		else
  			$curl -> setPostAttributes (json_decode ($postVars));
  	}

  	$retrieved = $curl -> retrieve ();
  	
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
