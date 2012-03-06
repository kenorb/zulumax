<?php

	function get_next_sort_link ($view, $title, $name, $defaultSorting = 'ASC', $template = '<th style="%th-styles">%link</th>')
	{
		$link = '<a href="?sort_by=' . $name . '&sort_order=';
		
		$current = ($view -> exposed_raw_input ['sort_by'] == $name) ? $view -> exposed_raw_input ['sort_order'] : null;
		
		if ($current === null)
			$order = false;
		else
		if ($current == 'DESC')
			$order = 'ASC';
		else
			$order = 'DESC';
		
		$link .= $order ? $order : $defaultSorting;
		
		$link .= '">' . $title . ' <span class="' . ($current ? ('custom-sorting-icon-' . strtolower ($current)) : '') . '"></a>'; 
		
		$template	= str_replace ('%link',			$link,	$template);
		$template	= str_replace ('%th-styles',	'',		$template);
		
		return $template;
	}
	
?>