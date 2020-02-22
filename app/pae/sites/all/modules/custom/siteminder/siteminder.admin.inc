<?php
/**
* Set up the siteminder administation page
*/
function siteminder_admin_settings() {
  
	$siteminder = new Siteminder();

	// Build options list based on HTTP headers.
	$headers = array();
	foreach ($_SERVER as $key => $value) {
		if (strpos($key, 'HTTP_') === 0) {
			$headers[$key] = $key;
		}
	}

	$form = array();
	
	array_unshift($headers, t('- Select a header -'));
	
	$form['siteminder_sid'] = array(
		'#type' => 'select',
		'#title' => t('Siteminder ID'),
		'#options' => $headers,
		'#required' => TRUE,
		'#default_value' => variable_get('siteminder_sid', set_default( 'siteminder_sid', 'HTTP_SMGOV_USERGUID' ) ),
		'#description' => t("The header field that maps to a unique identifier for a given user."),
	);
	
	$form['siteminder_username'] = array(
		'#type' => 'select',
		'#title' => t('Username'),
		'#options' => $headers,
		'#required' => TRUE,
		'#default_value' => variable_get('siteminder_username', set_default( 'siteminder_username', 'HTTP_SM_USER' ) ),
		'#description' => t("Header fields that map to the Drupal user's username. Enter one field per line. The fields will be concatenated together with a space-separator."),
	);	
		
	$form['siteminder_email'] = array(
		'#type' => 'select',
		'#title' => t('Email'),
		'#options' => $headers,
		'#required' => TRUE,
		'#default_value' => variable_get('siteminder_email', set_default( 'siteminder_email', 'HTTP_SMGOV_USEREMAIL' ) ),
		'#description' => t("The header field that maps to the Drupal user's email address"),
	);
	
	$roles = user_roles(TRUE);
	$form['siteminder_roles'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Default Roles'),
		'#default_value' => variable_get('siteminder_roles', ''),
		'#options' => $roles,
		'#required' => TRUE,
		'#description' => $roles ? t('New users will be assigned to these roles automatically upon account creation.') : t('You must first add some custom roles in order to assign users to them upon account creation.'),
	);
	
	$form['siteminder_logout_url'] = array(
		'#type' => 'select',
		'#title' => t('Logout URL'),
		'#options' => array(
			'https://logondev.gov.bc.ca/clp-cgi/logoff.cgi' => 'https://logondev.gov.bc.ca',
			'https://logontest.gov.bc.ca/clp-cgi/logoff.cgi' => 'https://logontest.gov.bc.ca',
			'https://logon.gov.bc.ca/clp-cgi/logoff.cgi' => 'https://logon.gov.bc.ca',
		),
		'#required' => TRUE,
		'#default_value' => variable_get('siteminder_logout_url', ''),
		'#description' => t("Select the Siteminder logout URL for the current environment."), 
	);
	
	// Pass the form array through system_settings_form()
	return system_settings_form($form);

  }

	function set_default( $key, $default ){
		$value = variable_get( $key );
		if ( !$value ){
			variable_set($key, $default);
		}
	}
