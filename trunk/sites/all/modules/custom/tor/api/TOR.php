<?php
	
class TOR
{
  
  public static function getCurrentAddress ()
  {
    global $base_url;
  
    $httpHost = $base_url;
    
    $curl			= curl_init ();
    
    curl_setopt ($curl, CURLOPT_CONNECTTIMEOUT,	10);
    curl_setopt ($curl, CURLOPT_TIMEOUT,				10);
    curl_setopt ($curl, CURLOPT_URL,						'http://whatismyip.org/');
    curl_setopt ($curl, CURLOPT_PROXY,					'http://' . variable_get ('tor_serverIP', '127.0.0.1') . ':' . variable_get ('tor_serverPort', 9050) . '/');
    curl_setopt ($curl, CURLOPT_PROXYPORT,			variable_get ('tor_serverPort', 9050));
    curl_setopt ($curl, CURLOPT_PROXYTYPE,			CURLPROXY_SOCKS5);
    curl_setopt ($curl, CURLOPT_RETURNTRANSFER,	1);
    
    @$ip = curl_exec ($curl);
    
    if (curl_errno ($curl) != 0)
      $ip = null;
    
    curl_close ($curl);
    
    return trim ($ip);
  }
  
  public static function queryAddress ($tor_ip = '127.0.0.1', $control_port = '9050', $auth_code = '')
  {
    $fp = fsockopen ($tor_ip, $control_port, $errno, $errstr, 30);
    
    if (!$fp)
    //can't connect to the control port
      return false;

    fputs ($fp, "AUTHENTICATE \"$auth_code\"\r\n");
    
    $response = fread($fp, 1024);
    
    list($code, $text) = explode(' ', $response, 2);
    
    if ($code != '250')
    //authentication failed
      return false; 
    
    //send the request to for new identity
    fputs($fp, "signal NEWNYM\r\n");
    
    $response = fread($fp, 1024);
    
    list($code, $text) = explode(' ', $response, 2);
    
    if ($code != '250')
    //signal failed
      return false;
    
    fclose($fp);
    
//		echo "<br />IP Changed<br />";
    
    return true;
    
  }
  
  public static function renewAddress ($tor_ip = null, $control_port = null, $auth_code = '')
  {
    if ($tor_ip === null)
      $tor_ip = variable_get ('tor_serverIP', '127.0.0.1');
    
    if ($control_port === null)
      $control_port = variable_get ('tor_serverControlPort');
    
    if ($auth_code == '')
      $auth_code = variable_get ('tor_serverControlPassword');
    
    $ipListSize			= variable_get ('tor_serverIPsPool');
    
    $tries					= 50; // Maybe, someday.. ;-)

    $cacheFilePath	= sys_get_temp_dir () . '/TOR.LastIPs';
      
    if (!file_exists ($cacheFilePath))
      file_put_contents ($cacheFilePath, json_encode (array ()));
      
    $ipList		= json_decode (file_get_contents ($cacheFilePath));
    
    while ($tries --)
    {
      self::queryAddress ($tor_ip, $control_port, $auth_code);
      
      $addrTries = 30;
      
      while ($addrTries --)
      {		
        $newIP	= self::getCurrentAddress ();
        
        if (!in_array ($newIP, $ipList))
        // Good IP
          break;
      }
      
      if (!in_array ($newIP, $ipList))
      // IP not in list, using it
      {
        array_push ($ipList, $newIP);
        
        if (count ($ipList) > $ipListSize)
        // There's more than $ipListSize entries then we pops up the first IP in the array
        {
          $oldIP = array_shift (&$ipList);
        }
        
        // We have an IP so we may break
        break;
      }
    }
    
    file_put_contents ($cacheFilePath, json_encode ($ipList));
  }
  
  public static function loadCookie ($filename)
  {
    $cookie = file_get_contents ($filename);
    
    //convert the cookie to hexadecimal
    $hex = '';
    
    for  ($i=0; $i < strlen ($cookie); $i++)
    {
      $h = dechex (ord ($cookie [$i]));
      
      $hex .= str_pad ($h, 2, '0', STR_PAD_LEFT);
    }
    
    return strtoupper ($hex);
  }
  
}

