# PAE Drupal

```bash
docker-compose exec drupal /bin/bash

wait-for db:3306 -- /usr/bin/yes | /usr/local/bin/drush site-install standard install_configure_form.update_status_module='array(FALSE,FALSE)' --db-url=mysql://${MYSQL_USER}:${MYSQL_PASSWORD}@${MYSQL_HOST}/${MYSQL_DATABASE} --account-name=${DRUPAL_ADMIN_USER} --account-pass=${DRUPAL_ADMIN_PASSWORD} --account-mail=${DRUPAL_ADMIN_EMAIL} --site-name=${DRUPAL_SITE_NAME} --site-mail=${DRUPAL_ADMIN_EMAIL} -r /var/www/html

cat <<\EOF >> /var/www/html/sites/default/settings.php
$conf['file_temporary_path'] = '/tmp';
$conf['file_public_path'] = 'sites/default/files';
$conf['file_private_path'] = 'sites/default/files/private';
$conf['site_mail'] = 'gary.t.wong@gov.bc.ca';
$conf['update_notify_emails'] = 'gary.t.wong@gov.bc.ca';
$conf['site_name'] = 'PAE Local';
$conf['preprocess_css'] = '0';
$conf['preprocess_js'] = '0';
EOF


mkdir -p /var/www/html/sites/default/files/private && \
chown -R www-data:www-data /var/www/html/sites/default/files && \
cp /tmp/private-htaccess /var/www/html/sites/default/files/private/.htaccess
```

```
drush vset maintenance_mode 1
```


GET PAE code (Stash!) and DB..
```bash
drush sqlc < /tmp/PAE-2019-12-18T13-54-28.mysql
```

drush utf8mb4-convert-databases

Update settings.php as per https://www.drupal.org/project/utf8mb4_convert


 'charset' => 'utf8mb4',
  'collation' => 'utf8mb4_general_ci',

    array (
      'database' => 'pae',
      'username' => 'pae',
      'password' => 'pae',
      'charset' => 'utf8mb4',
      'collation' => 'utf8mb4_general_ci',
      'host' => 'db',
      'port' => '',
      'driver' => 'mysql',
      'prefix' => '',
    ),





```
drush vset maintenance_mode 0
```


## Sample log (need to redo with enabled modules in place)

```
root@af211303cf4f:/var/www/html# drush @none dl utf8mb4_convert-7.x
Project utf8mb4_convert (7.x-1.0) downloaded to /root/.drush/utf8mb4_convert.                                                                            [success]
Project utf8mb4_convert contains 0 modules: .
root@af211303cf4f:/var/www/html# drush cc drush 
'drush' cache was cleared.                                                                                                                               [success]
root@af211303cf4f:/var/www/html# drush utf8mb4-convert-databases
This will convert the following databases to utf8mb4: default
Back up your databases before continuing! Continue? (y/n): y
Target MySQL database: pae@db (default:default)
Converting database: pae
Converting table: actions
Converting field: actions.aid
Converting field: actions.type
Converting field: actions.callback
Converting field: actions.label
Converting table: authmap
Converting field: authmap.authname
Converting field: authmap.module
Converting table: batch
Converting field: batch.token
Converting table: block
Converting field: block.module
Converting field: block.delta
Converting field: block.theme
Converting field: block.region
Converting field: block.pages
Converting field: block.title
Converting table: block_custom
Converting field: block_custom.body
Converting field: block_custom.info
Converting field: block_custom.format
Converting table: block_node_type
Converting field: block_node_type.module
Converting field: block_node_type.delta
Converting field: block_node_type.type
Converting table: block_role
Converting field: block_role.module
Converting field: block_role.delta
Converting table: blocked_ips
Converting field: blocked_ips.ip
Converting table: cache
Converting field: cache.cid
Converting table: cache_block
Converting field: cache_block.cid
Converting table: cache_bootstrap
Converting field: cache_bootstrap.cid
Converting table: cache_field
Converting field: cache_field.cid
Converting table: cache_filter
Converting field: cache_filter.cid
Converting table: cache_form
Converting field: cache_form.cid
Converting table: cache_image
Converting field: cache_image.cid
Converting table: cache_menu
Converting field: cache_menu.cid
Converting table: cache_page
Converting field: cache_page.cid
Converting table: cache_path
Converting field: cache_path.cid
Converting table: comment
Converting field: comment.subject
Converting field: comment.hostname
Converting field: comment.thread
Converting field: comment.name
Converting field: comment.mail
Converting field: comment.homepage
Converting field: comment.language
Converting table: date_format_locale
Converting field: date_format_locale.format
Converting field: date_format_locale.type
Converting field: date_format_locale.language
Converting table: date_format_type
Converting field: date_format_type.type
Converting field: date_format_type.title
Converting table: date_formats
Converting field: date_formats.format
Converting field: date_formats.type
Converting table: field_config
Converting field: field_config.field_name
Converting field: field_config.type
Converting field: field_config.module
Converting field: field_config.storage_type
Converting field: field_config.storage_module
Converting table: field_config_instance
Converting field: field_config_instance.field_name
Converting field: field_config_instance.entity_type
Converting field: field_config_instance.bundle
Converting table: field_data_body
Converting field: field_data_body.entity_type
Converting field: field_data_body.bundle
Converting field: field_data_body.language
Converting field: field_data_body.body_value
Converting field: field_data_body.body_summary
Converting field: field_data_body.body_format
Converting table: field_data_comment_body
Converting field: field_data_comment_body.entity_type
Converting field: field_data_comment_body.bundle
Converting field: field_data_comment_body.language
Converting field: field_data_comment_body.comment_body_value
Converting field: field_data_comment_body.comment_body_format
Converting table: field_data_field_image
Converting field: field_data_field_image.entity_type
Converting field: field_data_field_image.bundle
Converting field: field_data_field_image.language
Converting field: field_data_field_image.field_image_alt
Converting field: field_data_field_image.field_image_title
Converting table: field_data_field_tags
Converting field: field_data_field_tags.entity_type
Converting field: field_data_field_tags.bundle
Converting field: field_data_field_tags.language
Converting table: field_revision_body
Converting field: field_revision_body.entity_type
Converting field: field_revision_body.bundle
Converting field: field_revision_body.language
Converting field: field_revision_body.body_value
Converting field: field_revision_body.body_summary
Converting field: field_revision_body.body_format
Converting table: field_revision_comment_body
Converting field: field_revision_comment_body.entity_type
Converting field: field_revision_comment_body.bundle
Converting field: field_revision_comment_body.language
Converting field: field_revision_comment_body.comment_body_value
Converting field: field_revision_comment_body.comment_body_format
Converting table: field_revision_field_image
Converting field: field_revision_field_image.entity_type
Converting field: field_revision_field_image.bundle
Converting field: field_revision_field_image.language
Converting field: field_revision_field_image.field_image_alt
Converting field: field_revision_field_image.field_image_title
Converting table: field_revision_field_tags
Converting field: field_revision_field_tags.entity_type
Converting field: field_revision_field_tags.bundle
Converting field: field_revision_field_tags.language
Converting table: file_managed
Converting field: file_managed.filename
Converting field: file_managed.uri
Converting field: file_managed.filemime
Converting table: file_usage
Converting field: file_usage.module
Converting field: file_usage.type
Converting table: filter
Converting field: filter.format
Converting field: filter.module
Converting field: filter.name
Converting table: filter_format
Converting field: filter_format.format
Converting field: filter_format.name
Converting table: flood
Converting field: flood.event
Converting field: flood.identifier
Converting table: history
Converting table: image_effects
Converting field: image_effects.name
Converting table: image_styles
Converting field: image_styles.name
Converting field: image_styles.label
Converting table: menu_custom
Converting field: menu_custom.menu_name
Converting field: menu_custom.title
Converting field: menu_custom.description
Converting table: menu_links
Converting field: menu_links.menu_name
Converting field: menu_links.link_path
Converting field: menu_links.router_path
Converting field: menu_links.link_title
Converting field: menu_links.module
Converting table: menu_router
Converting field: menu_router.path
Converting field: menu_router.access_callback
Converting field: menu_router.page_callback
Converting field: menu_router.delivery_callback
Converting field: menu_router.tab_parent
Converting field: menu_router.tab_root
Converting field: menu_router.title
Converting field: menu_router.title_callback
Converting field: menu_router.title_arguments
Converting field: menu_router.theme_callback
Converting field: menu_router.theme_arguments
Converting field: menu_router.description
Converting field: menu_router.position
Converting field: menu_router.include_file
Converting table: node
Converting field: node.type
Converting field: node.language
Converting field: node.title
Converting table: node_access
Converting field: node_access.realm
Converting table: node_comment_statistics
Converting field: node_comment_statistics.last_comment_name
Converting table: node_revision
Converting field: node_revision.title
Converting field: node_revision.log
Converting table: node_type
Converting field: node_type.type
Converting field: node_type.name
Converting field: node_type.base
Converting field: node_type.module
Converting field: node_type.description
Converting field: node_type.help
Converting field: node_type.title_label
Converting field: node_type.orig_type
Converting table: queue
Converting field: queue.name
Converting table: rdf_mapping
Converting field: rdf_mapping.type
Converting field: rdf_mapping.bundle
Converting table: registry
Converting field: registry.name
Converting field: registry.type
Converting field: registry.filename
Converting field: registry.module
Converting table: registry_file
Converting field: registry_file.filename
Converting field: registry_file.hash
Converting table: role
Converting field: role.name
Converting table: role_permission
Converting field: role_permission.permission
Converting field: role_permission.module
Converting table: search_dataset
Converting field: search_dataset.type
Converting field: search_dataset.data
Converting table: search_index
Converting field: search_index.word
Converting field: search_index.type
Converting table: search_node_links
Converting field: search_node_links.type
Converting field: search_node_links.caption
Converting table: search_total
Converting field: search_total.word
Converting table: semaphore
Converting field: semaphore.name
Converting field: semaphore.value
Converting table: sequences
Converting table: sessions
Converting field: sessions.sid
Converting field: sessions.ssid
Converting field: sessions.hostname
Converting table: shortcut_set
Converting field: shortcut_set.set_name
Converting field: shortcut_set.title
Converting table: shortcut_set_users
Converting field: shortcut_set_users.set_name
Converting table: system
Converting field: system.filename
Converting field: system.name
Converting field: system.type
Converting field: system.owner
Converting table: taxonomy_index
Converting table: taxonomy_term_data
Converting field: taxonomy_term_data.name
Converting field: taxonomy_term_data.description
Converting field: taxonomy_term_data.format
Converting table: taxonomy_term_hierarchy
Converting table: taxonomy_vocabulary
Converting field: taxonomy_vocabulary.name
Converting field: taxonomy_vocabulary.machine_name
Converting field: taxonomy_vocabulary.description
Converting field: taxonomy_vocabulary.module
Converting table: url_alias
Converting field: url_alias.source
Converting field: url_alias.alias
Converting field: url_alias.language
Converting table: users
Converting field: users.name
Converting field: users.pass
Converting field: users.mail
Converting field: users.theme
Converting field: users.signature
Converting field: users.signature_format
Converting field: users.timezone
Converting field: users.language
Converting field: users.init
Converting table: users_roles
Converting table: variable
Converting field: variable.name
Converting table: watchdog
Converting field: watchdog.type
Converting field: watchdog.message
Converting field: watchdog.link
Converting field: watchdog.location
Converting field: watchdog.referer
Converting field: watchdog.hostname
Finished converting the default:default MySQL database!
root@af211303cf4f:/var/www/html# vi  sites/default/settings.php 
root@af211303cf4f:/var/www/html# drush cc all 
'all' cache was cleared. 
```