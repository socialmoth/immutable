// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_BASIC_SLICE_HPP
#define IMMUTABLE_BASIC_SLICE_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <immutable/details/basic_string.hpp>

#include <iterator>
#include <string>

namespace immutable {
inline namespace v1 {
namespace details {

template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_slice {
public: // Member types
    using traits_type = Traits;
    using value_type = const CharT;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = reference;
    using pointer = value_type*;
    using const_pointer = pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<iterator>;

public: // Constants
    static constexpr const size_type npos = -1;

private:
    pointer data_;
    size_type size_;

public: // Constructors
    constexpr basic_slice() noexcept
      : data_{nullptr}
      , size_{0}
    {}

    constexpr basic_slice(const basic_slice& other) noexcept = default;

    constexpr basic_slice(pointer data, size_type size) noexcept
      : data_{data}
      , size_{size}
    {}

    constexpr basic_slice(pointer data) noexcept
      : data_{data}
      , size_{traits_type::length(data)}
    {}

    constexpr basic_slice(const basic_string<CharT, Traits>& s) noexcept
      : basic_slice{s.data(), s.size()}
    {}

    template<typename Allocator>
    constexpr basic_slice(const std::basic_string<CharT, Traits, Allocator>& s) noexcept
      : basic_slice{s.data(), s.size()}
    {}

    // template<std::contiguous_iterator First, std::sized_sentinel_for<First> Last>
    template<typename First, typename Last>
    constexpr basic_slice(First first, Last last)
      : data_{std::to_address(first)}
      , size_{static_cast<size_type>(std::distance(first, last))}
    {}

    template<typename Range>
    constexpr basic_slice(Range&& rng)
      : basic_slice{std::begin(rng), std::end(rng)}
    {}

    constexpr basic_slice(std::nullptr_t) = delete;

public: // Assignment
    constexpr basic_slice& operator=(const basic_slice& view) noexcept = default;


public: // Element access
    constexpr const_reference at(size_type pos) const
    {
        if (pos >= size())
            throw std::out_of_range("pos");
        return data()[pos];
    }

    constexpr const_reference operator[](size_type pos) const noexcept
    {
        return data()[pos];
    }

    constexpr const_reference front() const noexcept
    {
        return data()[0];
    }

    constexpr const_reference back() const noexcept
    {
        return data()[size() - 1];
    }

    constexpr const_pointer data() const noexcept
    {
        return data_;
    }

public: // Iterators
    constexpr const_iterator begin() const noexcept
    {
        return data();
    }

    constexpr const_iterator cbegin() const noexcept
    {
        return data();
    }

    constexpr const_iterator end() const noexcept
    {
        return data() + size() + 1;
    }

    constexpr const_iterator cend() const noexcept
    {
        return data() + size() + 1;
    }

    constexpr const_reverse_iterator rbegin() const noexcept
    {
        return {begin()};
    }

    constexpr const_reverse_iterator crbegin() const noexcept
    {
        return {begin()};
    }

    constexpr const_reverse_iterator rend() const noexcept
    {
        return {end()};
    }

    constexpr const_reverse_iterator crend() const noexcept
    {
        return {end()};
    }

public: // Capacity
    /// Returns `true` if the string has zero code units.
    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return size() == 0;
    }

    /// Returns the number of code units in the string
    constexpr size_type size() const noexcept
    {
        return size_;
    }
};

} // namespace details
} // namespace v1
} // namespace immutable

#endif // !defined(IMMUTABLE_BASIC_SLICE_HPP)
