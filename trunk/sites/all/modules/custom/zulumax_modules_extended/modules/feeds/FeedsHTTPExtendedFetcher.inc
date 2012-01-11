<?php

require_once dirname (__FILE__) . '/../../extensions/Curl.php';

class FeedsHTTPExtendedFetcherResult extends FeedsFetcherResult
{
	protected $config;

  public function __construct ($config)
  {
    parent::__construct ($config ['source']);
    
    $this -> config = $config;
  }

  public function getRaw ()
  {
  	$url			= $this -> config ['source'];
  	$postVars	= $this -> config ['postVars'];
  	
  	$curl			= new Curl ($url);
  	
  	$curl -> setReferer ('http://zulutrade.com/Performance.aspx');
  	$curl -> setHeaders (array ('Content-type: application/json'));
  	
  	if ($postVars)
  		$curl -> setPostContent ($postVars);

  	$retrieved = $curl -> retrieve ();
  	
  	echo $retrieved;
  	
  	exit;
  }
}

/**
 * Fetches data via HTTP.
 */
class FeedsHTTPExtendedFetcher extends FeedsHTTPFetcher
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
	     
			'postVars' => array (
	      '#type'						=> 'textarea',
	      '#title'					=> t('POST variables'),
	      '#description'		=> t('POST variables in JSON format, e.g.: {userId:3,userName:"Sonic"}'),
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
		
		return new FeedsHTTPExtendedFetcherResult ($source_config);
	}
	

}
