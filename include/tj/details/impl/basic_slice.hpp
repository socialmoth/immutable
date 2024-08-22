// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef TJ_STRING_BASIC_SLICE_IMPL_HPP
#define TJ_STRING_BASIC_SLICE_IMPL_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <tj/details/basic_slice.hpp>

namespace tj {
inline namespace v1 {

template<typename CharT, typename Traits>
inline constexpr basic_slice<CharT, Traits>::basic_slice() noexcept
  : data_{nullptr}
  , size_{0}
{}

template<typename CharT, typename Traits>
inline constexpr basic_slice<CharT, Traits>::basic_slice(pointer data, size_type size) noexcept
  : data_{data}
  , size_{size}
{}

template<typename CharT, typename Traits>
inline constexpr basic_slice<CharT, Traits>::basic_slice(pointer data) noexcept
  : data_{data}
  , size_{traits_type::length(data)}
{}

template<typename CharT, typename Traits>
inline constexpr basic_slice<CharT, Traits>::basic_slice(
    const basic_string<CharT, Traits>& s) noexcept
  : basic_slice{s.data(), s.size()}
{}

template<typename CharT, typename Traits>
template<typename Allocator>
inline constexpr basic_slice<CharT, Traits>::basic_slice(
    const std::basic_string<CharT, Traits, Allocator>& s) noexcept
  : basic_slice{s.data(), s.size()}
{}

template<typename CharT, typename Traits>
template<typename First, typename Last>
inline constexpr basic_slice<CharT, Traits>::basic_slice(First first, Last last)
  : data_{std::to_address(first)}
  , size_{static_cast<size_type>(std::distance(first, last))}
{}

template<typename CharT, typename Traits>
template<typename Range>
inline constexpr basic_slice<CharT, Traits>::basic_slice(Range&& rng)
  : basic_slice{std::begin(rng), std::end(rng)}
{}

template<typename CharT, typename Traits>
inline constexpr auto basic_slice<CharT, Traits>::get_data() const noexcept -> const_pointer
{
    return data_;
}

template<typename CharT, typename Traits>
inline constexpr auto basic_slice<CharT, Traits>::get_size() const noexcept -> size_type
{
    return size_;
}

} // namespace v1
} // namespace tj

#endif // !defined(TJ_STRING_BASIC_SLICE_IMPL_HPP)
