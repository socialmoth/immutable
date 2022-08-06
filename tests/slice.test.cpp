// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#include <immutable/string.hpp>

#include "compile_time_tests.hpp"

#include <cstring>
#include <doctest.h>
#include <vector>

namespace immutable {
inline namespace v1 {
namespace test {

TEST_CASE("default constructible"
          * doctest::description("immutable::slice is default constructible")
          * doctest::test_suite("slice"))
{
    const slice ss;
    CHECK(ss.size() == 0);       // default constructed string views must be empty,
    CHECK(ss.data() == nullptr); // and point at nothing.
}

TEST_CASE("character pointer construction"
          * doctest::description("immutable::slice can be constructed from a character pointer")
          * doctest::test_suite("slice"))
{
    const char* s = "hello, world";
    const slice ss{s};
    CHECK(ss.data() == s);
    CHECK(ss.size() == strlen(s));
}

TEST_CASE("immutable::string construction"
          * doctest::description("immutable::slice can be constructed from immutable::string")
          * doctest::test_suite("slice"))
{
    const string s{"hello, world"};
    const slice ss{s};
    CHECK(ss.data() == s.data());
    CHECK(ss.size() == s.size());
}

TEST_CASE("std::string construction"
          * doctest::description("immutable::slice can be constructed from std::string")
          * doctest::test_suite("slice"))
{
    const std::string s{"hello, world"};
    const slice ss{s};
    CHECK(ss.data() == s.data());
    CHECK(ss.size() == s.size());
}

TEST_CASE("character pointer construction"
          * doctest::description("immutable::slice can be constructed from std::vector<char>")
          * doctest::test_suite("slice"))
{
    const char s[] = "hello, world";
    const std::vector<char> v{std::begin(s), std::end(s)};
    const slice ss{v};
    CHECK(ss.data() == v.data());
    CHECK(ss.size() == v.size());
}

TEST_CASE("copy construction" * doctest::description("immutable::slice can be copy-constructed")
          * doctest::test_suite("slice"))
{
    const slice ss1{"hello, world"};
    const slice ss2{ss1};
    CHECK(ss1.data() == ss2.data());
    CHECK(ss1.size() == ss2.size());
}

TEST_CASE("not constructible from nullptr"
          * doctest::description("immutable::slice cannot be constructed from nullptr")
          * doctest::test_suite("slice"))
{
    CHECK(!constructible_from_nullptr_v<slice>);
}

} // namespace test
} // namespace v1
} // namespace immutable
