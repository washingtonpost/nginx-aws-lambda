cmake_minimum_required(VERSION 3.0.2)
project(nginx_aws_lambda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#this will locate the aws sdk for c++ package so that we can use its targets
#set(aws-sdk-cpp_DIR "/Users/findleyr/Library/Caches/CLion2016.2/cmake/generated/aws-sdk-cpp-2bb67d43/2bb67d43/Debug0")
find_package(aws-sdk-cpp)

include_directories(include)

file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(nginx_aws_lambda STATIC ${SOURCES})

#since we called find_package(), this will resolve all dependencies, header files, and cflags necessary
#to build and link your executable.
target_link_libraries(nginx_aws_lambda aws-cpp-sdk-lambda)

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS nginx_aws_lambda DESTINATION /usr/lib)
install(FILES ${HEADERS} DESTINATION include/nginx_aws_lambda)
