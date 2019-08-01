cmake_minimum_required(VERSION 3.10)
project(test_package)

find_package(svd-alias REQUIRED)

add_executable(test_package main.cpp)
target_link_libraries(test_package svd-alias::svd-alias)
