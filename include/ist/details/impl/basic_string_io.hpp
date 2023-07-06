// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef ISTLIB_BASIC_STRING_IO_IMPL_HPP
#define ISTLIB_BASIC_STRING_IO_IMPL_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <ist/details/basic_string_range.hpp>

#include <iosfwd>

namespace ist {
inline namespace v1 {
namespace details {

template<typename CharT, typename Traits, typename Derived>
inline std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                     const basic_string_range<CharT, Traits, Derived>& s)
{
    return os.write(s.data(), s.size());
}

} // namespace details
} // namespace v1
} // namespace ist

#endif // !defined(ISTLIB_BASIC_STRING_IO_IMPL_HPP)
