# Copyright Teis Johansen 2020
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
cmake_minimum_required(VERSION 3.12)
project(ist VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_ISTLIB_TESTS "Build ist unit tests" ON)

add_subdirectory(external)

set(ISTLIB ${PROJECT_NAME})
add_library(${ISTLIB} INTERFACE)
target_include_directories(${ISTLIB} INTERFACE include)

if(BUILD_ISTLIB_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
