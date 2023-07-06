// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef ISTLIB_DETAILS_LITERAL_STRING_HPP
#define ISTLIB_DETAILS_LITERAL_STRING_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <cstddef>

namespace ist {
inline namespace v1 {
namespace details {

template<std::size_t N>
struct literal_string {
    char data[N] {};
    static constexpr std::size_t size = N - 1;

    constexpr literal_string(const char (&s)[N]) noexcept
    {
        for (std::size_t i = 0; i < N; ++i)
            data[i] = s[i];
    }
};

} // namespace details
} // inline namespace v1
} // namespace ist

#endif // !defined(ISTLIB_DETAILS_LITERAL_STRING_HPP)
