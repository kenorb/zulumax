<?php

	require_once 'sites/all/modules/custom/deathbycaptcha/deathbycaptcha.module';
	
	var_dump (deathbycaptcha_solve_url ('http://s2.blomedia.pl/vbeta.pl/images//2010/04/captcha-painting-1-gautam-rao-copy.jpg', $captchaId));
	
?>