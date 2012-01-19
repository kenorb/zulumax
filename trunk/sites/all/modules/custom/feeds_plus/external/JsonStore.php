<?php
/* JSONStore 0.4 - JSON structure as storage
 *
 * Copyright (c) 2007 Stefan Goessner (goessner.net)
 * Licensed under the MIT (MIT-LICENSE.txt) licence.
 */

class JsonStore {
   function toString($obj) {
      $json = json_decode ($obj);
   }
   function asObj($jsonstr) {
      $json = json_encode ($jsonstr, JSON_UNESCAPED_UNICODE);
   }
   function& get(&$obj, $expr) {
      if (($expr = JsonStore::_normalizedFirst($obj, $expr)) !== false) {
		 $o =& $obj;
         $keys = preg_split("/([\"'])?\]\[([\"'])?/", preg_replace(array("/^\\$\[[\"']?/", "/[\"']?\]$/"), "", $expr));
		 for ($i=0; $i<count($keys); $i++)
			 $o =& $o[$keys[$i]];
		 return $o;
	  }
	  return null;
   }
   function set(&$obj, $expr, $value) {
	  if ($res =& JsonStore::get($obj, $expr))
	     $res = $value;
   }
   function add(&$obj, $parentexpr, $value, $name="") {
	  $parent =& JsonStore::get($obj, $parentexpr);
	  if ($name != "") $parent[$name] = $value;
	  else             $parent[] = $value;
   }
   function remove(&$obj, $expr) {
      if (($expr = JsonStore::_normalizedFirst($obj, $expr)) !== false) {
		 $o =& $obj;
         $keys = preg_split("/([\"'])?\]\[([\"'])?/", preg_replace(array("/^\\$\[[\"']?/", "/[\"']?\]$/"), "", $expr));
		 for ($i=0; $i<count($keys)-1; $i++)
			$o =& $o[$keys[$i]];
		 unset($o[$keys[$i]]);
		 return true;
	  }
	  return false;
   }
   function _normalizedFirst($o, $expr) {
	  if ($expr == "")
		  return false;
	  else if (preg_match("/^\$(\[([0-9*]+|'[-a-zA-Z0-9_ ]+')\])*$/", $expr)) {
		  print("normalized: " . $expr);
		  return $expr;
	  }
	  else {
		  $res = jsonPath($o, $expr, array("resultType" => "PATH"));
		  return $res ? $res[0] : $res;
	  }
   }
}
?>