// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_SLICE_HPP
#define IMMUTABLE_SLICE_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <immutable/details/basic_slice.hpp>

namespace immutable {
inline namespace v1 {

using slice = details::basic_slice<char>;

} // namespace v1
} // namespace immutable

#endif // !defined(IMMUTABLE_SLICE_HPP)
