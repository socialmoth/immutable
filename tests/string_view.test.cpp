// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#include <immutable/string.hpp>
#include <immutable/string_view.hpp>

#include "compile_time_tests.hpp"

#include <doctest.h>

namespace immutable {
inline namespace v1 {
namespace test {

TEST_CASE("default constructible"
          * doctest::description("immutable::string_view is default constructible")
          * doctest::test_suite("string_view"))
{
    const string_view sv;
    CHECK(sv.size() == 0);       // default constructed string views must be empty,
    CHECK(sv.data() == nullptr); // and point at nothing.
}

TEST_CASE(
    "character pointer construction"
    * doctest::description("immutable::string_view can be constructed from a character pointer")
    * doctest::test_suite("string_view"))
{
    const char* s = "hello, world";
    const string_view sv{s};
    CHECK(sv.data() == s); // The C-style string constructor must point at the original string,
    CHECK(sv.size() == strlen(s)); // and the lengths must match.
}

TEST_CASE("character pointer construction"
          * doctest::description("immutable::string_view can be constructed from immutable::string")
          * doctest::test_suite("string_view"))
{
    const string s{"hello, world"};
    const string_view sv{s};
    CHECK(sv.data()
          == s.data()); // The immutable::string constructor must point at the original string,
    CHECK(sv.size() == s.size()); // and the lengths must match.
}


TEST_CASE("character pointer construction"
          * doctest::description("immutable::string_view can be constructed from std::string")
          * doctest::test_suite("string_view"))
{
    const std::string s{"hello, world"};
    const string_view sv{s};
    CHECK(sv.data() == s.data()); // The std::string constructor must point at the original string,
    CHECK(sv.size() == s.size()); // and the lengths must match.
}

TEST_CASE("copy construction"
          * doctest::description("immutable::string_view can be copy-constructed")
          * doctest::test_suite("string_view"))
{
    const string_view sv1{"hello, world"};
    const string_view sv2{sv1};
    CHECK(sv1.data() == sv2.data());
    CHECK(sv1.size() == sv1.size());
}

TEST_CASE("not constructible from nullptr"
          * doctest::description("immutable::string_view cannot be constructed from nullptr")
          * doctest::test_suite("string_view"))
{
    CHECK(!constructible_from_nullptr_v<string_view>);
}

} // namespace test
} // namespace v1
} // namespace immutable
