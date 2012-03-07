<?php
	
	class ProxyChanger
	{
		
		public static function getCurrentProxy ()
		{
			$configuration = proxychanger_get_config ();
			
			if (!$configuration -> proxyChangerEnabled)
			// Disabled
				return null;
				
			if (!($servers = proxychanger_get_server_list ()))
				return null;
				
			$currentServerId = $configuration -> proxyChangerServerCurrent ?: 0;
			
			if ($currentServerId >= count ($servers))
				variable_set ('proxyChangerServerCurrent', $currentServerId = 0);
			
			return $servers [$currentServerId];
		}
		
		public static function renewProxy (&$usedProxies)
		{
			$currentProxyId					= variable_get ('proxyChangerServerCurrent');
			$servers						= proxychanger_get_server_list ();
			
			$usedProxies [$currentProxyId]	= true;
				
			if (($currentProxyId + 1) >= count ($servers))
			// Last proxy in list
				variable_set ('proxyChangerServerCurrent', $currentProxyId = 0);
			else
				variable_set ('proxyChangerServerCurrent', $currentProxyId = ++$currentProxyId);
			
			if (@$usedProxies [$currentProxyId])
			// Already used proxy
				return false;
			
			$usedProxies [$currentProxyId]	= true;
			
			return true;
		}
	}

?>