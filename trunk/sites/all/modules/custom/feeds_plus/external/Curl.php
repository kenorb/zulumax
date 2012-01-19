<?php

/**
 * Curl, a curl_* helper
 * @var string $method
 * @var string $address
 * @var string $referer
 * @var array $atributesGet
 * @var array $atributesPost
 *
 * Example:
 *
 *   $curl = new Curl ('http://www.google.com/search');
 *   $curl -> setGetAttribute ('hl', 'pl');
 *   $curl -> setGetAttribute ('q',  'searching phrase');
 *   echo $curl -> receive ();
 *
 */
class Curl
{
    const					Post	= 'post';
    const					Get		= 'get';
    const					PostModeArray		= 0;
    const					PostModeContent = 1;

    private					$attributesPostMode;
    private					$method;			// Curl::Post or Curl::Get
    private					$address;			// E.g. 'http://www.google.com/search'
    private					$referer;			// Default to the specified address
    private					$attributesGet;		// Get attributes array
    private					$attributesPost;	// Post attributes array
    private					$cookiesFilePath;
    private					$user;
    private					$password;
    private					$info;
    public static		$cookiesReceived;
    private					$responseHeader;
    private					$sessionId;
    private					$proxyIP;
    private					$proxyUserName;
    private					$proxyUserPassword;
    private					$proxyPort;
    private					$followSteps;
    private					$userAgent;
    private					$requestHeaders;
    private static			$curl;

    public function			__construct				($address = '')
    {
    		$this -> attributesPostMode = self::PostModeArray;
        $this -> address					= $address;
        $this -> referer					= $address;
        $this -> method						= self::Get;
        $this -> attributesGet		= array ();
        $this -> attributesPost		= array ();
        $this -> cookiesFilePath	= '/tmp/CurlCookies.ncf';
        $this -> requestHeaders		= array ();

        self::$cookiesReceived		= array ();
    }

    /**
     * Initializes curl, sets required options and receives the result
     * @return string Page reveived
     */
    public function			retrieve					()
    {
        static $curl;
        
				if (!$curl)
					$curl = curl_init ();
				
				if ($this -> proxyIP != null)
				{
					curl_setopt ($curl, CURLOPT_PROXY,		'http://' . $this -> proxyIP);

					list ($host, $port) = array ($this -> proxyIP, $this -> proxyPort);

					if (isset ($port))
						curl_setopt ($curl, CURLOPT_PROXYPORT,	$port);

					curl_setopt ($curl, CURLOPT_PROXYTYPE,	CURLPROXY_SOCKS5);
				}
        
        if ($this -> attributesPost)
        {
            $this -> setMethod (self::Post);

            curl_setopt ($curl, CURLOPT_POST, 1);

            if ($this -> attributesPostMode == self::PostModeArray)
            {
	            
	            $postAttributes = array ();
	
	            foreach ($this -> attributesPost as $name => $value)
	            	$postAttributes [] = $name . '=' . urlencode ($value);
	            
	            curl_setopt ($curl, CURLOPT_POSTFIELDS, implode ('&', $postAttributes));
            }
            else
            if ($this -> attributesPostMode == self::PostModeContent)
            {
            	curl_setopt ($curl, CURLOPT_POSTFIELDS, $this -> attributesPost);
            }
        }
        
        $getPlainAttributes = '';

        if ($this -> attributesGet)
        {
            $getPlainAttributes = '?';

            $getAttributes = array ();

            foreach ($this -> attributesGet as $name => $value)
            	$getAttributes [] = $name . '=' . urlencode ($value);

            $getPlainAttributes .= implode ('&', $getAttributes);
        }

        if ($this -> user)
        {
            curl_setopt($curl, CURLOPT_USERPWD, $this->user . ':' . $this -> password);
        }
        
        curl_setopt ($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_setopt ($curl, CURLOPT_URL,						$this -> address . $getPlainAttributes);
        curl_setopt ($curl, CURLOPT_REFERER,				$this -> referer);
        curl_setopt ($curl, CURLOPT_FOLLOWLOCATION,	$this -> followSteps == 0 ? 0 : 1);
        curl_setopt ($curl, CURLOPT_USERAGENT,			$this -> userAgent !== null ? $this -> userAgent : 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:2.0.1) Gecko/20100101 Firefox/4.0.1');
        curl_setopt ($curl, CURLOPT_TIMEOUT,				30);
        curl_setopt ($curl, CURLOPT_HEADER,					0);
        curl_setopt ($curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt ($curl, CURLOPT_COOKIEJAR,			realpath ($this -> cookiesFilePath));
        curl_setopt ($curl, CURLOPT_COOKIEFILE,			realpath ($this -> cookiesFilePath));
        curl_setopt ($curl, CURLOPT_COOKIESESSION,  FALSE);
        curl_setopt ($curl, CURLOPT_HTTPHEADER,  		$this -> requestHeaders);
        curl_setopt ($curl, CURLOPT_ENCODING,				'UTF-8');
        

        $result = curl_exec ($curl);
        
				if (curl_errno ($curl))
					echo curl_error ($curl);

        
        $this -> info = curl_getinfo ($curl);

//        curl_close ($curl);

        $this -> receiveCookies ();

        $this -> setGetAttributes (array ());
        $this -> setPostAttributes (array ());
        
        return $result;
    }

    public function getInfo()
    {
        return $this -> info;
    }

    public function			setCookiesPath			($path)
    {
        $this -> cookiesFilePath = $path;
    }
		
		public function			setProxy						($ip, $port, $userName = null, $password = null)
		{
			$this -> proxyIP						= $ip;
			$this -> proxyPort					= $port;
			$this -> proxyUserName			= $userName;
			$this -> proxyUserPassword	= $password;
		}
		
    /**
     * Gets a cookie by name
     * @param string $name
     * @return CurlCookie CurlCookie or null
     */
    public function			receiveCookies			()
    {
        clearstatcache ();

        $cookieLines				= @file ($this -> cookiesFilePath);
        self::$cookiesReceived		= array ();

        if ($cookieLines)
        foreach ($cookieLines as $line)
        {
            if (substr (ltrim ($line), 0, 1) === '#')
            // Comment
            continue;

            if (!strlen (trim ($line)))
            // Empty line
            continue;

            // Exploding cookie information
            $cookie = new CurlCookie ();
            $cookie -> fromNetscapePlain ($line);

            self::$cookiesReceived [$cookie -> getName ()] = $cookie;
        }


    }

    public function			hasCookie				($name)
    {
        return array_key_exists ($name, self::$cookiesReceived);
    }

    public function	getCookies				()
    {
        return self::$cookiesReceived;
    }

    /**
     * Returns received cookie by name
     * @param string $name
     * @return CurlCookie A Cookie
     */
    public static function	getCookie				($name)
    {
        if (self::$cookiesReceived === null)
        self::receiveCookies ();

        if (!array_key_exists ($name, self::$cookiesReceived))
        throw new Exception ("Can't get cookie '$name', cookie doesn't exist");

        return self::$cookiesReceived [$name];
    }

    public function			setCookies				(/* List of CurlCookie instances*/)
    {
        $file = fopen ($this -> cookiesFilePath, 'w');

        fwrite ($file, "# Netscape HTTP Cookie File\r\n# http://curl.haxx.se/rfc/cookie_spec.html\r\n# This file was generated by libcurl! Edit at your own risk.\r\n\r\n");

        $cookiesArray = array ();

        // Forming netscape compatible cookie
        foreach (func_get_args () as $cookie)
        $cookiesArray [] = $cookie -> toNetscapePlain ();

        if ($this -> sessionId !== null)
        {
            //$sessionCookie		= new CurlCookie ('', 'PHPSESSID', $this -> sessionId, 3600*2);
            //$cookiesArray []	= $sessionCookie -> toNetscapePlain ();
        }

        fwrite ($file, implode ("\r\n", $cookiesArray) . "\r\n");
        fclose ($file);
    }

    /**
     * Sets a GET attribute
     * @param string $name Name of the attribute
     * @param mixed $value Value of the attribute
     */
    public function			setGetAttribute			($name, $value)
    {
        $this -> attributesGet [$name] = $value;
    }

    /**
     * Sets GET attributes by the array
     * @param array $attributes An array of 'attributeName' => 'attributeValue' pairs
     */
    public function			setGetAttributes		($attributes)
    {
        $this -> attributesGet = $attributes;
    }

    /**
     * Sets a POST attribute and changes the request method to be a POST request
     * @param string $name Name of the attribute
     * @param mixed $value Value of the attribute
     */
    public function			setPostAttribute		($name, $value)
    {
        $this -> attributesPost [$name] = $value;
    }
    
    public function			setPostContent			($value)
    {
    	$this -> attributesPostMode	= self::PostModeContent;
    	$this -> attributesPost			= $value;
    }
    
    public function			setHeaders					($headers)
    {
    	$this -> requestHeaders = $headers;
    }
    

    public function setCredentials( $user, $password)
    {
        $this -> user = $user;
        $this -> password = $password;
    }

    /**
     * Sets POST attributes by the array
     * @param array $attributes An array of 'attributeName' => 'attributeValue' pairs
     */
    public function			setPostAttributes		($attributes)
    {
        $this -> attributesPost = $attributes;
    }

    /**
     * Sets the request method
     * @param string $method Curl::Get | Curl::Post
     */
    public function			setMethod				($method)
    {
        $this -> method = $method;
    }

    /**
     * Sets the refer address
     * @param string $referer Referer address
     */
    public function			setReferer				($referer)
    {
        $this -> referer	= $referer;
    }

    public function			getResponseHeader		()
    {
        return $this -> responseHeader;
    }

    public function			useCurrentSession		()
    {
        $this -> sessionId = session_id ();
    }

    public function         setAddress              ( $url )
    {
    		$this -> referer = $this -> address;
        $this -> address = $url;
    }
    
    public function		setUserAgent		($userAgent)
    {
    	$this -> userAgent = $userAgent;
    }
    
    public function		getUserAgent		()
    {
    	return $this -> userAgent;
    }
    
    public function		setFollowSteps ($steps)
    {
    	$this -> followSteps = $steps;
    }

}



/**
 * Represents a Curl cookie
 */
class CurlCookie
{
    protected				$name;
    protected				$domain;
    protected				$expirationDate;
    protected				$value;

    public function			__construct				($domain = null, $name = null, $value = null, $expirationDate = null)
    {
        if ($expirationDate === null)
        $expirationDate = 0;

        $this -> domain			= $domain;
        $this -> expirationDate	= $expirationDate;
        $this -> name			= $name;
        $this -> value			= $value;

    }

    public function			getName					()
    {
        return $this -> name;
    }

    public function			getDomain				()
    {
        return $this -> domain;
    }

    public function			getExpirationDate		()
    {
        return $this -> expirationDate;
    }

    public function			getExpirationDateString	()
    {
        return date ('Y-m-d H:i:s', $this -> expirationDate);
    }

    public function			getValue				()
    {
        return $this -> value;
    }

    public function			fromNetscapePlain		($line)
    {
        // Delimiter is a TAB (\t)
        list ($domain, $dummy1, $dummy2, $dummy3, $expirationDate, $name, $value) = explode ("\t", trim ($line));

        $this -> domain			= $domain;
        $this -> expirationDate	= $expirationDate;
        $this -> name			= $name;
        $this -> value			= $value;

        return $this;
    }

    public function			toNetscapePlain			()
    {
        return	$this -> domain . "\tFALSE\tFALSE\t" . $this -> expirationDate . "\t" . $this -> name . "\t" . urlencode ($this -> value);
    }

}

?>