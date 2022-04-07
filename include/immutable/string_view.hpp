// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_STRING_VIEW_HPP
#define IMMUTABLE_STRING_VIEW_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <immutable/details/basic_string_view.hpp>

namespace immutable {
inline namespace v1 {

using string_view = details::basic_string_view<char>;

} // namespace v1
} // namespace immutable

#endif // !defined(IMMUTABLE_STRING_VIEW_HPP)
