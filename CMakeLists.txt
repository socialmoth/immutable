# Copyright Teis Johansen 2020
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
cmake_minimum_required(VERSION 3.12)
project(immutable VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_IMMUTABLE_TESTS "Build immutable unit tests" ON)

add_subdirectory(external)

set(IMMUTABLE_LIB ${PROJECT_NAME})
add_library(${IMMUTABLE_LIB} INTERFACE)
target_include_directories(${IMMUTABLE_LIB} INTERFACE include)

if(BUILD_IMMUTABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
