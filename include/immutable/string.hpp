// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_STRING_HPP
#define IMMUTABLE_STRING_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <string>

namespace immutable {
inline namespace v1 {

template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_slice;

template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_string;

template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_string_view;

using slice = basic_slice<char>;
using string = basic_string<char>;
using string_view = basic_string_view<char>;

using wslice = basic_slice<wchar_t>;
using wstring = basic_string<wchar_t>;
using wstring_view = basic_string<wchar_t>;

namespace details {

template<typename CharT, typename Traits, typename Derived>
class basic_string_range;

}

} // namespace v1
} // namespace immutable


#include <immutable/details/basic_string_range.hpp>
#include <immutable/details/basic_slice.hpp>
#include <immutable/details/basic_string.hpp>
#include <immutable/details/basic_string_view.hpp>

#include <immutable/details/impl/basic_string_range.hpp>
#include <immutable/details/impl/basic_slice.hpp>
#include <immutable/details/impl/basic_string.hpp>
#include <immutable/details/impl/basic_string_view.hpp>

#include <immutable/details/impl/basic_string_io.hpp>

#endif // !defined(IMMUTABLE_STRING_HPP)
