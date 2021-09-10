// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_DETAILS_LITERAL_STRING_HPP
#define IMMUTABLE_DETAILS_LITERAL_STRING_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <cstddef>

namespace immutable {
inline namespace v1 {
namespace details {

template<std::size_t N>
struct literal_string {
    char chars_[N] {};
    
    constexpr literal_string(const char (&s)[N]) noexcept
    {
        for (std::size_t i = 0; i < N; ++i)
            chars_[i] = s[i];
    }
};

} // namespace details
} // inline namespace v1
} // namespace immutable

#endif // !defined(IMMUTABLE_DETAILS_LITERAL_STRING_HPP)
