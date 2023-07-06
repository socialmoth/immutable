// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef ISTLIB_BASIC_STRING_RANGE_HPP
#define ISTLIB_BASIC_STRING_RANGE_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <cstring>
#include <iterator>
#include <stdexcept>
#include <type_traits>

namespace ist {
inline namespace v1 {
namespace details {

template<typename CharT, typename Traits, typename Derived>
class basic_string_range {
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

public:
    static constexpr const size_type npos = -1;

public: // Element access
    constexpr const_reference at(size_type pos) const;
    constexpr const_reference operator[](size_type pos) const noexcept;
    constexpr const_reference front() const noexcept;
    constexpr const_reference back() const noexcept;
    constexpr pointer data() const noexcept;

public: // Iterators
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator cbegin() const noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cend() const noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_reverse_iterator rend() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

public: // Capacity
    /// Returns `true` if the string has zero code units.
    [[nodiscard]] constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;

public: // Operations
        //    constexpr int compare(const basic_string& rhs) const noexcept
        //    {
        //        // TODO: Since we know the length of both strings, we can do better than
        //        // this.
        //        return compare(rhs.data());
        //    }
        //
        //    constexpr int compare(pointer rhs) const noexcept
        //    {
        //        const auto lhs = data();
        //        if (lhs == rhs)
        //            return 0;
        //        // TODO: This is only valid for basic_string<char>
        //        return strcmp(lhs, rhs);
        //    }
public: // Operations
    template<class T>
    constexpr int compare(T&&) const noexcept
        requires(std::is_convertible_v<T, basic_slice<CharT, Traits>>);
    constexpr int compare(basic_slice<CharT, Traits> rhs) const noexcept;

    // constexpr bool contains(basic_slice s) const noexcept;
    // constexpr bool contains(value_type c) const noexcept;
    // constexpr bool contains(pointer p) const noexcept;

public: // Search
        // constexpr size_type find(basic_slice str, size_type pos = 0) const noexcept;
        // constexpr size_type find(pointer p, size_type pos = 0) const noexcept;
        // constexpr size_type find(value_type c, size_type pos = 0) const noexcept;
        // constexpr size_type find(pointer s, size_type pos, size_type count) const noexcept;
};

#if __has_include(<compare>)
#    if __cpp_impl_three_way_comparison >= 201907L && __cpp_lib_three_way_comparison >= 201907L
#        define IMMUTABLE_HAS_SPACESHIP 1
#        include <compare>
#    endif
#endif

#ifdef IMMUTABLE_HAS_SPACESHIP

template<typename T, typename CharT, typename Traits, typename Derived>
inline constexpr auto operator<=>(const basic_string_range<CharT, Traits, Derived>& lhs,
                                  const T& rhs) noexcept
    requires(std::is_convertible_v<T, basic_slice<CharT, Traits>>)
{
    const auto order = lhs.compare(static_cast<basic_slice<CharT, Traits>>(rhs));
    if (order < 0) {
        return std::strong_ordering::less;
    } else if (order == 0) {
        return std::strong_ordering::equal;
    } else if (order > 0) {
        return std::strong_ordering::greater;
    }
}

template<typename T, typename CharT, typename Traits, typename Derived>
inline constexpr bool operator==(const basic_string_range<CharT, Traits, Derived>& lhs,
                                 const T& rhs) noexcept
    requires(std::is_convertible_v<T, basic_slice<CharT, Traits>>)
{
    return lhs.compare(static_cast<basic_slice<CharT, Traits>>(rhs)) == 0;
}

#else
#    define IMMUTABLE_DEFINE_COMPARISON_OPERATOR(op)                                               \
        template<typename T, typename CharT, typename Traits, typename Derived>                    \
        inline constexpr bool operator op(                                                         \
            const basic_string_range<CharT, Traits, Derived>& lhs,                                 \
            const T& rhs) noexcept requires(std::is_convertible_v<T, basic_slice<CharT, Traits>>)  \
        {                                                                                          \
            return lhs.compare(static_cast<basic_slice<CharT, Traits>>(rhs)) op 0;                 \
        }

IMMUTABLE_DEFINE_COMPARISON_OPERATOR(==)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(!=)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(<)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(<=)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(>)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(>=)
#    undef IMMUTABLE_DEFINE_COMPARISON_OPERATOR
#endif // IMMUTABLE_HAS_SPACESHIP

#undef IMMUTABLE_HAS_SPACESHIP

} // namespace details
} // namespace v1
} // namespace ist

#endif // !defined(ISTLIB_BASIC_STRING_RANGE_HPP)
