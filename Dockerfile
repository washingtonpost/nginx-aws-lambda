FROM debian

# Install dependencies
RUN apt-get update
RUN apt-get install -y wget zip tar build-essential gcc libpcre3 libpcre3-dev zlib1g-dev libssl-dev cmake git libcurl4-openssl-dev uuid-dev

# Fetch aws c++ sdk
WORKDIR /
RUN wget https://github.com/aws/aws-sdk-cpp/archive/master.zip
RUN unzip master.zip

# Compile aws c++ sdk
RUN mkdir aws-sdk-cpp-build
WORKDIR /aws-sdk-cpp-build
RUN cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_ONLY="lambda" /aws-sdk-cpp-master
RUN make
RUN make install

# Compile c++ lambda wrapper
#WORKDIR /
#RUN mkdir nginx-aws-lambda
#COPY . /nginx-aws-lambda
#RUN mkdir nginx-aws-lambda-build
#WORKDIR /nginx-aws-lambda-build
#RUN cmake -DCMAKE_BUILD_TYPE=Release /nginx-aws-lambda
#RUN make
#RUN make install

# Fetch nginx source code
WORKDIR /
RUN wget http://nginx.org/download/nginx-1.11.5.tar.gz
RUN tar xf nginx-1.11.5.tar.gz

# Copy module
RUN mkdir ngx-module
COPY ngx-module/. /ngx-module

# Compile nginx
WORKDIR nginx-1.11.5