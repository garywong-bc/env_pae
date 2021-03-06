<?php
	
	class Siteminder {

		public $account;
		public $uid;
		public $sid;
		public $username;
		public $email;
		
		private $sidHeaderKey;
		private	$usernameHeaderKey;
		private $emailHeaderKey;
		private $locationHeaderKey;		
		
		public function __construct(){				
			$this->siteminderSetHeaderKeys();
			$this->siteminderSetUserInfo();
		}		
		
		/**
		 * Check if a user account exists
		 */		 
		public function userAccountExists() {		
			$userAccount = FALSE;		
			if ( $this->sid ) {
				if ( $this->uid = $this->getUserId( $this->sid ) ) {
					$userAccount = TRUE;
				}  
			}		
			return $userAccount;
		}
				
		/**
		 * Creates a new user account
		 */
		public function createUserAccount() {
						
			if ( $this->sid ) {
				global $user;
				$authName = $_SERVER['HTTP_SM_AUTHDIRNAME'];
				$data = array();
				$data['name'] = str_replace('\\', '-', $this->username);

				if ( $authName && strcasecmp( $authName, 'IDIR' ) == 0 && strpos( $this->username, 'IDIR' ) !== 0 ) {
					$data['name'] = 'IDIR-' . $this->username;
				}
	
				$data['mail'] = $this->email;
				$data['pass'] = user_password();			
				$data['status'] = 1;
				$data['roles'] = variable_get('siteminder_roles', NULL);
				if ( $account = user_save( null, $data ) ) {
					$sm_data = array(
						'sid' => $this->sid,
						'uid' => $account->uid,
					);
					$record = drupal_write_record( 'siteminder', $sm_data );
				}				
			  	if ( $account ) {
					$user = user_load( $account->uid );
					user_login_finalize();
					$this->account = $user;
				}				
			} else {
				watchdog(
					'siteminder', 
					'Unable to create user account.  The Siteminder object: %siteminder', 
					array('%siteminder' => print_r( get_object_vars ( $this ), TRUE )), 
					WATCHDOG_ERROR );
				drupal_access_denied();
				exit();
			}
		}

		/**
		 * Log user into Drupal
		 */
		public function userLogin() {		
			global $user;			
			if ( $this->uid ) {
				$user = user_load( $this->uid );
				user_login_finalize();
				$this->account = $user;
			} else {
				watchdog(
					'siteminder', 
					'Unable to login user.  The Siteminder object: %siteminder', 
					array('%siteminder' => print_r( get_object_vars ( $this ), TRUE )), 
					WATCHDOG_ERROR );
			}
		}
		
		/**
		 * Get the appropriate HTTP Request header key from variables
		 */
		private function siteminderSetHeaderKeys() {			
			$this->sidHeaderKey = variable_get('siteminder_sid');
			$this->usernameHeaderKey = variable_get('siteminder_username');
			$this->emailHeaderKey = variable_get('siteminder_email');
		}
		
		/**
		 * Set the user information from the SM session header 
		 */
		private function siteminderSetUserInfo() {
			$this->sid = array_key_exists($this->sidHeaderKey, $_SERVER) ? $_SERVER[$this->sidHeaderKey]: FALSE;
			$this->username = array_key_exists($this->usernameHeaderKey, $_SERVER) ? $_SERVER[$this->usernameHeaderKey]: NULL;
			$this->email = array_key_exists($this->emailHeaderKey, $_SERVER) ? $_SERVER[$this->emailHeaderKey]: NULL;
		}		
			
		/**
		 * Fetch the uid for $this->sid.  This query will return false if $this->sid does not exist.
		 */
		private static function getUserId( $sid ) {
			return db_query("SELECT uid FROM {siteminder} WHERE sid = :sid", array(':sid' => $sid))->fetchField();
		}
	
	}

?>