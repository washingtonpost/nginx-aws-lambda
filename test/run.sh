#!/bin/bash

./configure --with-ld-opt="-lstdc++" --add-module=/ngx-module
make
make install

# Add /usr/local/nginx/conf/nginx.conf
cp /test/nginx.conf /usr/local/nginx/conf/nginx.conf

# start nginx
/usr/local/nginx/sbin/nginx "-g daemon off;"
