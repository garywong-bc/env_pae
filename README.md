# PAE Drupal

Dockerized version of PAE D7.

## Test for conversion to utf8mb4

```bash
drush utf8mb4-convert-databases
```

Update settings.php as per https://www.drupal.org/project/utf8mb4_convert

```bash
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

## To enable/disable Maintenance mode

```bash
drush vset maintenance_mode 0
```


## Sample log (need to redo with enabled modules in place)

```bash
root@af211303cf4f:/var/www/pae# drush @none dl utf8mb4_convert-7.x
Project utf8mb4_convert (7.x-1.0) downloaded to /root/.drush/utf8mb4_convert.                                                                            [success]
Project utf8mb4_convert contains 0 modules: .
root@af211303cf4f:/var/www/pae# drush cc drush 
'drush' cache was cleared.                                                                                                                               [success]
root@af211303cf4f:/var/www/pae# drush utf8mb4-convert-databases
This will convert the following databases to utf8mb4: default
Back up your databases before continuing! Continue? (y/n): y
Target MySQL database: pae@db (default:default)
...
Finished converting the default:default MySQL database!
```

## Generate list of Modules in PAE D7 DLVR

Commands include:

```bash
drush @none dl utf8mb4_convert-7.x
drush cc drush
```