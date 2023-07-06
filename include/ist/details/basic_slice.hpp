// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef ISTLIB_BASIC_SLICE_HPP
#define ISTLIB_BASIC_SLICE_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <ist/details/basic_string_range.hpp>

#include <iterator>
#include <string>

namespace ist {
inline namespace v1 {

template<typename CharT, typename Traits>
class basic_slice : public details::basic_string_range<CharT, Traits, basic_slice<CharT, Traits>> {
public: // Member types
    using base_type = details::basic_string_range<CharT, Traits, basic_string_view<CharT, Traits>>;

    using traits_type = base_type::traits_type;
    using value_type = base_type::value_type;
    using size_type = base_type::size_type;
    using difference_type = base_type::difference_type;
    using reference = base_type::reference;
    using const_reference = base_type::const_reference;
    using pointer = base_type::pointer;
    using const_pointer = base_type::const_pointer;
    using iterator = base_type::iterator;
    using const_iterator = base_type::const_iterator;
    using reverse_iterator = base_type::reverse_iterator;
    using const_reverse_iterator = base_type::const_reverse_iterator;

private:
    pointer data_;
    size_type size_;

public: // Constructors
    constexpr basic_slice() noexcept;
    constexpr basic_slice(const basic_slice& other) noexcept = default;
    constexpr basic_slice(pointer data, size_type size) noexcept;
    constexpr basic_slice(pointer data) noexcept;

    constexpr basic_slice(const basic_string<CharT, Traits>& s) noexcept;

    template<typename Allocator>
    constexpr basic_slice(const std::basic_string<CharT, Traits, Allocator>& s) noexcept;

    // template<std::contiguous_iterator First, std::sized_sentinel_for<First> Last>
    template<typename First, typename Last>
    constexpr basic_slice(First first, Last last);

    template<typename Range>
    constexpr basic_slice(Range&& rng);

    constexpr basic_slice(std::nullptr_t) = delete;

public: // Assignment
    constexpr basic_slice& operator=(const basic_slice& view) noexcept = default;

public: // basic_string_range
    //friend base_type;
    constexpr const_pointer get_data() const noexcept;
    constexpr size_type get_size() const noexcept;
};

} // namespace v1
} // namespace ist

#endif // !defined(ISTLIB_BASIC_SLICE_HPP)
