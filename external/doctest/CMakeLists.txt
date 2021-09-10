# Copyright Teis Johansen 2020
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
set(DOCTEST_LIB "doctest")
add_library(${DOCTEST_LIB} INTERFACE)
target_include_directories(${DOCTEST_LIB} INTERFACE include)
