// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_STRING_HPP
#define IMMUTABLE_STRING_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <immutable/details/basic_string.hpp>

namespace immutable {
inline namespace v1 {

using string = basic_string<char>;

namespace details {

using string_literal_ref = basic_literal_string_ref<char>;

} // namespace details

} // namespace v1
} // namespace immutable

#if __cpp_nontype_template_args < 201911

namespace immutable {
inline namespace v1 {
namespace literals {

string operator""_is(const char* str, std::size_t len)
{
    return string(details::string_literal_ref{str, len});
}

} // namespace literals
} // namespace v1
} // namespace immutable

#else // if compiler supports non-type template args

#    include <immutable/details/literal_string.hpp>

namespace immutable {
inline namespace v1 {
namespace literals {

template<details::literal_string Literal>
constexpr string operator""_is()
{
    return string(details::literal_string_ref{&Literal.data[0], Literal.size});
}

} // namespace literals
} // namespace v1
} // namespace immutable

#endif // if compiler supports non-type template args

#endif // !defined(IMMUTABLE_STRING_HPP)
