// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#include <ist/string.hpp>

#include "compile_time_tests.hpp"

#include <doctest.h>


namespace immutable {
inline namespace v1 {
namespace test {

TEST_CASE("default constructible"
          * doctest::description("immutable::string is default constructible")
          * doctest::test_suite("string"))
{
    const string s;
    CHECK(s.size() == 0);       // default constructed strings must be empty,
    CHECK(s.data() != nullptr); // but not null.
    CHECK(*s.data() == '\0');
}

TEST_CASE("literal construction"
          * doctest::description("immutable::string can be constructed from a string literal")
          * doctest::test_suite("string"))
{
    const string s{"hello, world"};
    CHECK(s.size() == strlen("hello, world"));
}

TEST_CASE("user-defined literal construction"
          * doctest::description("immutable::string can be constructed from a user-defined literal")
          * doctest::test_suite("string"))
{
    using namespace immutable::literals;
    const string s = "hello, world"_is;
    CHECK(s.size() == strlen("hello, world"));
}

TEST_CASE("character pointer construction"
          * doctest::description("immutable::string can be constructed from a character pointer")
          * doctest::test_suite("string"))
{
    const char* s = "hello, world";
    const string s1{s};
    CHECK(s1.data() != s); // The C-style string constructor has to allocate memory,
    CHECK(s1 == s);        // but the contents must be the same.
}

TEST_CASE("copy construction" * doctest::description("immutable::string can be copy-constructed")
          * doctest::test_suite("string"))
{
    const string l1{"hello, world"};
    const string l2{l1};           // You can create a copy of a literal,
    CHECK(l2.data() == l1.data()); // but it must be shallow

    const string h1{l1.data()};
    const string h2{h1};           // You can create a copy of a heap-allocated string,
    CHECK(h2.data() == h1.data()); // but it must _not_ allocate additional memory
    CHECK(h1.data() != l1.data()); // h1 must be heap-allocated
}

TEST_CASE("not constructible from nullptr"
          * doctest::description("immutable::string cannot be constructed from nullptr")
          * doctest::test_suite("string"))
{
    CHECK(!constructible_from_nullptr_v<string>);
}

TEST_CASE("assignable from string literal"
          * doctest::description("immutable::string can be assigned to string literal")
          * doctest::test_suite("string"))
{
    using namespace immutable::literals;
    auto s = "hello"_is;
    s = "goodbye";
    CHECK(s == "goodbye");
}

TEST_CASE("not assignable from nullptr"
          * doctest::description("immutable::string cannot be assigned to nullptr")
          * doctest::test_suite("string"))
{
    CHECK(!assignable_from_nullptr_v<string>);
}

} // namespace test
} // namespace v1
} // namespace immutable
