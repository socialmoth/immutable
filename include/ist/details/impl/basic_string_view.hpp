// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef ISTLIB_BASIC_STRING_VIEW_IMPL_HPP
#define ISTLIB_BASIC_STRING_VIEW_IMPL_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <string>

namespace immutable {
inline namespace v1 {

template<typename CharT, typename Traits>
inline constexpr basic_string_view<CharT, Traits>::basic_string_view() noexcept
  : data_{nullptr}
  , size_{0}
{}

template<typename CharT, typename Traits>
inline constexpr basic_string_view<CharT, Traits>::basic_string_view(pointer data) noexcept
  : data_{data}
  , size_{traits_type::length(data)}
{}

template<typename CharT, typename Traits>
inline constexpr basic_string_view<CharT, Traits>::basic_string_view(
    const basic_string<CharT, Traits>& s) noexcept
  : data_{s.data()}
  , size_{s.size()}
{}

template<typename CharT, typename Traits>
template<typename Allocator>
inline constexpr basic_string_view<CharT, Traits>::basic_string_view(
    const std::basic_string<CharT, Traits, Allocator>& s) noexcept
  : data_{s.data()}
  , size_{s.size()}
{}

template<typename CharT, typename Traits>
inline constexpr auto basic_string_view<CharT, Traits>::c_str() const noexcept -> const_pointer
{
    return this->data();
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string_view<CharT, Traits>::get_data() const noexcept -> const_pointer
{
    return data_;
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string_view<CharT, Traits>::get_size() const noexcept -> size_type
{
    return size_;
}

} // namespace v1
} // namespace immutable

#endif // !defined(ISTLIB_BASIC_STRING_VIEW_IMPL_HPP)
