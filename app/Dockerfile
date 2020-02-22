# NOTE SHA signature may need to be updated for new releases of composer, see 
# https://getcomposer.org/download/
FROM drupal:7.67

ADD https://raw.githubusercontent.com/eficode/wait-for/master/wait-for wait-for

COPY ./files/private-htaccess ./files/PAE-2019-12-18T13-54-28.mysql \
	./files/PAEDelivery-2020-02-20T14-08-32.mysql \
	./files/pae-modules-themes.tar ./files/pae-dlvr-file.make /tmp/

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils \
	mysql-client \
	vim \
    netcat \
&& php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');" \
&& php -r "if (hash_file('sha384', 'composer-setup.php') === 'e0012edf3e80b6978849f5eff0d4b4e4c79ff1609dd1e613307e16318854d24ae64f26d17af3ef0bf7cfb710ca74755a') { echo 'Installer verified'; } else { echo 'Installer corrupt'; unlink('composer-setup.php'); } echo PHP_EOL;" \
&& php composer-setup.php \
&& php -r "unlink('composer-setup.php');" \
&& mv composer.phar /usr/local/bin/composer \
&& php -r "copy('https://github.com/drush-ops/drush/releases/download/8.3.2/drush.phar', 'drush.phar');" \
&& chmod +x drush.phar \
&& mv drush.phar /usr/local/bin/drush \
&& yes | drush init \
&& drush @none dl utf8mb4_convert-7.x \
&& drush cc drush \
&& chmod +x wait-for && mv wait-for /usr/local/bin/wait-for
