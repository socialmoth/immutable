// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef TJ_STRING_TESTS_COMPILE_TIME_HPP
#define TJ_STRING_TESTS_COMPILE_TIME_HPP

#include <type_traits>
#include <cstddef>
#include <utility>

namespace tj {
inline namespace v1 {
namespace test {

namespace details {

template<typename T> struct sink { using type = void; };
template<typename T> using sink_t = typename sink<T>::type;

}

#define COMPILE_TIME_TEST(name, ...) \
    template<typename T, typename = void> struct name : std::false_type {}; \
    template<typename T> struct name<T, details::sink_t<decltype(__VA_ARGS__)>> : std::true_type {}; \
    template<typename T> constexpr bool name##_v = name<T>::value

COMPILE_TIME_TEST(constructible_from_nullptr, T(nullptr));
COMPILE_TIME_TEST(assignable_from_nullptr, std::declval<T>() = nullptr);

#undef COMPILE_TIME_TEST

} // namespace test
} // namespace v1
} // namespace tj

#endif // !defined(TJ_STRING_TESTS_COMPILE_TIME_HPP)
