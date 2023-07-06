# Copyright Teis Johansen 2020
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
include(CTest)

set(ISTLIB_TESTS ${PROJECT_NAME}-tests)

add_executable(${ISTLIB_TESTS}
    slice.test.cpp
    string_view.test.cpp
    string.test.cpp
    main.test.cpp
)

target_compile_options(${ISTLIB_TESTS}
    PRIVATE
        --coverage -O0 -g
        -fsanitize=address,undefined
)

target_compile_definitions(${ISTLIB_TESTS}
    PRIVATE
        -DDEBUG
)

target_link_libraries(${ISTLIB_TESTS}
    PRIVATE
        ${ISTLIB}
        doctest
        --coverage
        asan
        ubsan
)

add_test(NAME "unit" COMMAND ${ISTLIB_TESTS})
