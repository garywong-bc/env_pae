<?php 

	function extended_user_account_terms(){  
	
		$extended_user_account_terms = variable_get('extended_user_account_terms', 'Terms of Use.');		
		$form['extended_user_account_terms'] = array(
			'#title' => t('Terms of Use'),
			'#type' => 'text_format',
			'#rows' => 5,
			'#format' => 'full_html',
			'#required' => TRUE,
			'#description' => t('This is the block content for the subscriptions block for users that already subscribe to this content.'),
			'#default_value' => check_markup( $extended_user_account_terms['value'], $extended_user_account_terms['format'] ),
			'#group' => 'messages',
		);
		
		return system_settings_form($form);
	}
?>