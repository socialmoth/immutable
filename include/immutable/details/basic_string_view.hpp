// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_BASIC_STRING_VIEW_HPP
#define IMMUTABLE_BASIC_STRING_VIEW_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <immutable/details/basic_slice.hpp>
#include <immutable/details/basic_string.hpp>

#include <string>

namespace immutable {
inline namespace v1 {
namespace details {

template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_string_view : public basic_slice<CharT, Traits>  {
public:
    using traits_type = basic_slice<CharT, Traits>::traits_type;
    using value_type = basic_slice<CharT, Traits>::value_type;
    using size_type = basic_slice<CharT, Traits>::size_type;
    using difference_type = basic_slice<CharT, Traits>::difference_type;
    using reference = basic_slice<CharT, Traits>::reference;
    using const_reference = basic_slice<CharT, Traits>::const_reference;
    using pointer = basic_slice<CharT, Traits>::pointer;
    using const_pointer = basic_slice<CharT, Traits>::const_pointer;
    using iterator = basic_slice<CharT, Traits>::iterator;
    using const_iterator = basic_slice<CharT, Traits>::const_iterator;
    using reverse_iterator = basic_slice<CharT, Traits>::reverse_iterator;
    using const_reverse_iterator = basic_slice<CharT, Traits>::const_reverse_iterator;

public: // Constructors
    constexpr basic_string_view() noexcept
      : basic_slice<CharT, Traits>{}
    {}

    constexpr basic_string_view(const basic_string_view& other) noexcept = default;

    constexpr basic_string_view(pointer data) noexcept
      : basic_slice<CharT, Traits>{data}
    {}

    constexpr basic_string_view(const basic_string<CharT, Traits>& s) noexcept
      : basic_slice<CharT, Traits>{s.data(), s.size()}
    {}

    template<typename Allocator>
    constexpr basic_string_view(const std::basic_string<CharT, Traits, Allocator>& s) noexcept
      : basic_slice<CharT, Traits>{s.data(), s.size()}
    {}

    constexpr basic_string_view(std::nullptr_t) = delete;

public: // Assignment
    constexpr basic_string_view& operator=(const basic_string_view& view) noexcept = default;


public: // Element access
    constexpr const_pointer c_str() const noexcept
    {
        return this->data();
    }
};

} // namespace details
} // namespace v1
} // namespace immutable

#endif // !defined(IMMUTABLE_BASIC_STRING_VIEW_HPP)
