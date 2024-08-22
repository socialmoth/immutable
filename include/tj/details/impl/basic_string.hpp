// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef TJ_STRING_BASIC_STRING_IMPL_HPP
#define TJ_STRING_BASIC_STRING_IMPL_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <tj/details/basic_string_range.hpp>

#include <algorithm>
#include <atomic>
#include <cstring>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace tj {
inline namespace v1 {

template<typename CharT, typename Traits>
inline constexpr basic_string<CharT, Traits>::basic_string() noexcept
  : size_{make_literal_size(0)}
{
    buf_.literal = &empty_literal_[0];
}

template<typename CharT, typename Traits>
inline constexpr basic_string<CharT, Traits>::basic_string(
    details::basic_literal_string_ref<CharT> literal) noexcept
  : size_{make_literal_size(literal.size)}
{
    buf_.literal = literal.data;
}

template<typename CharT, typename Traits>
template<basic_string<CharT, Traits>::size_type N>
inline basic_string<CharT, Traits>::basic_string(value_type (&data)[N]) noexcept
  : size_{make_external_size(N - 1)}
{
    buf_.external = make_external_buf(&data[0], N - 1);
}

template<typename CharT, typename Traits>
inline basic_string<CharT, Traits>::basic_string(pointer data)
  : basic_string{data, traits_type::length(data)}
{}

template<typename CharT, typename Traits>
inline basic_string<CharT, Traits>::basic_string(pointer data, size_type len)
  : size_{make_external_size(len)}
{
    buf_.external = make_external_buf(data, len);
}

template<typename CharT, typename Traits>
inline basic_string<CharT, Traits>::basic_string(const basic_string& other)
{
    copy(other);
}

template<typename CharT, typename Traits>
inline auto basic_string<CharT, Traits>::operator=(const basic_string& other) -> basic_string&
{
    release();
    copy(other);
    return *this;
}

template<typename CharT, typename Traits>
template<basic_string<CharT, Traits>::size_type N>
inline auto basic_string<CharT, Traits>::operator=(value_type (&data)[N]) -> basic_string&
{
    return (*this) = basic_string{data, N - 1};
}
template<typename CharT, typename Traits>
inline basic_string<CharT, Traits>::~basic_string()
{
    release();
}
template<typename CharT, typename Traits>
inline constexpr auto basic_string<CharT, Traits>::get_data() const noexcept -> const_pointer
{
    return c_str();
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string<CharT, Traits>::c_str() const noexcept -> const_pointer
{
    if (has_external_buffer())
        return external_data();
    return buf_.literal;
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string<CharT, Traits>::get_size() const noexcept -> size_type
{
    return size_ >> 1;
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string<CharT, Traits>::external_data() const noexcept -> char_type*
{
    return external_data(buf_.external);
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string<CharT, Traits>::external_data(external_buffer* external) noexcept -> char_type*
{
    return reinterpret_cast<char_type*>(reinterpret_cast<char*>(external)
                                        + sizeof(external_buffer));
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string<CharT, Traits>::make_literal_size(size_type n) -> size_type
{
    return (n << 1) | 0;
}

template<typename CharT, typename Traits>
inline constexpr auto basic_string<CharT, Traits>::make_external_size(size_type n) -> size_type
{
    return (n << 1) | 1;
}

template<typename CharT, typename Traits>
inline constexpr bool basic_string<CharT, Traits>::has_external_buffer() const noexcept
{
    return (size_ & 1) != 0;
}

template<typename CharT, typename Traits>
inline auto basic_string<CharT, Traits>::make_external_buf(pointer data, size_type len) -> external_buffer*
{
    const auto buf_size = (len + 1) * sizeof(value_type);
    const auto external = static_cast<external_buffer*>(malloc(sizeof(external_buffer) + buf_size));
    if (!external)
        throw std::bad_alloc();

    new (external) external_buffer{};
    memcpy(external_data(external), data, buf_size);
    return external;
}

template<typename CharT, typename Traits>
inline void basic_string<CharT, Traits>::copy(const basic_string& other) noexcept
{
    if (other.has_external_buffer()) {
        buf_.external = other.buf_.external;
        buf_.external->ref_count.fetch_add(1);
    } else {
        buf_.literal = other.buf_.literal;
    }
    size_ = other.size_;
}

template<typename CharT, typename Traits>
inline void basic_string<CharT, Traits>::release() noexcept
{
    if (has_external_buffer()) {
        const auto refs = buf_.external->ref_count.fetch_sub(1) - 1;
        if (refs == 0) {
            buf_.external->~external_buffer();
            free(buf_.external);
        }
    }
}

} // namespace v1
} // namespace tj


#if __cpp_nontype_template_args < 201911

namespace tj {
inline namespace v1 {
namespace literals {

template<typename CharT>
inline basic_string<CharT> operator""_is(const CharT* str, std::size_t len)
{
    return basic_string<CharT>{details::basic_literal_string_ref<CharT>{str, len}};
}

} // namespace literals
} // namespace v1
} // namespace tj

#else // if compiler supports non-type template args

#    include <tj/details/literal_string.hpp>

namespace tj {
inline namespace v1 {
namespace literals {

template<details::literal_string Literal>
inline constexpr string operator""_is()
{
    return string(details::literal_string_ref{&Literal.data[0], Literal.size});
}

} // namespace literals
} // namespace v1
} // namespace tj

#endif // if compiler supports non-type template args

#endif // !defined(TJ_STRING_BASIC_STRING_IMPL_HPP)
