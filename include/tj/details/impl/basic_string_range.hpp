// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef TJ_STRING_BASIC_STRING_RANGE_IMPL_HPP
#define TJ_STRING_BASIC_STRING_RANGE_IMPL_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <tj/details/basic_string_range.hpp>

namespace tj {
inline namespace v1 {
namespace details {

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::at(size_type pos) const
    -> const_reference
{
    if (pos >= size())
        throw std::out_of_range("pos");
    return data()[pos];
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto
basic_string_range<CharT, Traits, Derived>::operator[](size_type pos) const noexcept
    -> const_reference
{
    return data()[pos];
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::front() const noexcept
    -> const_reference
{
    return data()[0];
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::back() const noexcept
    -> const_reference
{
    return data()[size() - 1];
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::data() const noexcept -> pointer
{
    return static_cast<const Derived*>(this)->get_data();
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::begin() const noexcept
    -> const_iterator
{
    return data();
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::cbegin() const noexcept
    -> const_iterator
{
    return data();
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::end() const noexcept
    -> const_iterator
{
    return data() + size() + 1;
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::cend() const noexcept
    -> const_iterator
{
    return data() + size() + 1;
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::rbegin() const noexcept
    -> const_reverse_iterator
{
    return {begin()};
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::crbegin() const noexcept
    -> const_reverse_iterator
{
    return {begin()};
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::rend() const noexcept
    -> const_reverse_iterator
{
    return {end()};
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::crend() const noexcept
    -> const_reverse_iterator
{
    return {end()};
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr bool basic_string_range<CharT, Traits, Derived>::empty() const noexcept
{
    return size() == 0;
}

template<typename CharT, typename Traits, typename Derived>
inline constexpr auto basic_string_range<CharT, Traits, Derived>::size() const noexcept -> size_type
{
    return static_cast<const Derived*>(this)->get_size();
}


template<typename CharT, typename Traits, typename Derived>
inline constexpr int
basic_string_range<CharT, Traits, Derived>::compare(basic_slice<CharT, Traits> rhs) const noexcept
{
    const auto s1 = size();
    const auto s2 = rhs.size();
    if (s1 == 0 && s2 == 0)
        return 0;

    const auto order = traits_type::compare(data(), rhs.data(), std::min(s1, s2));
    if (order != 0)
        return order;

    if (s1 < s2)
        return -1;
    if (s1 == s2)
        return 0;
    return 1;
}

} // namespace details
} // namespace v1
} // namespace tj

#endif // !defined(TJ_STRING_BASIC_STRING_RANGE_IMPL_HPP)
