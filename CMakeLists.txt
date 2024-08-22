# Copyright Teis Johansen 2020
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
cmake_minimum_required(VERSION 3.12)
project(tj_string VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TJ_STRING_TESTS "Build ist unit tests" ON)

add_subdirectory(external)

set(TJ_STRING ${PROJECT_NAME})
add_library(${TJ_STRING} INTERFACE)
target_include_directories(${TJ_STRING} INTERFACE include)

if(BUILD_TJ_STRING_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
