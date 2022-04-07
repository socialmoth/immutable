# Copyright Teis Johansen 2020
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
include(CTest)

set(IMMUTABLE_TESTS ${PROJECT_NAME}-tests)

add_executable(${IMMUTABLE_TESTS}
    slice.test.cpp
    string_view.test.cpp
    string.test.cpp
    main.test.cpp
)

target_compile_options(${IMMUTABLE_TESTS}
    PRIVATE
        --coverage -O0 -g
        -fsanitize=address,undefined
)

target_compile_definitions(${IMMUTABLE_TESTS}
    PRIVATE
        -DDEBUG
)

target_link_libraries(${IMMUTABLE_TESTS}
    PRIVATE
        ${IMMUTABLE_LIB}
        doctest
        --coverage
        asan
        ubsan
)

add_test(NAME "unit" COMMAND ${IMMUTABLE_TESTS})
