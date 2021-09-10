// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef IMMUTABLE_BASIC_STRING_HPP
#define IMMUTABLE_BASIC_STRING_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <algorithm>
#include <atomic>
#include <cstring>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

#if __has_include(<compare>)
#    if __cpp_impl_three_way_comparison >= 201907L && __cpp_lib_three_way_comparison >= 201907L
#        define IMMUTABLE_HAS_SPACESHIP 1
#        include <compare>
#    endif
#endif

namespace immutable {
inline namespace v1 {

template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_string {
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

private:
    using char_type = CharT;

    struct external_buffer {
        std::atomic_size_t ref_count{1};
    };

    union buffer {
        value_type* literal;
        external_buffer* external;
    };

    static constexpr value_type empty_literal_[1] = {};

    size_type size_;
    buffer buf_;

public: // Constructors
    constexpr basic_string() noexcept
      : size_{make_literal_size(0)}
    {
        buf_.literal = &empty_literal_[0];
    }

    template<size_type N>
    constexpr explicit basic_string(value_type (&data)[N]) noexcept
      : size_{make_literal_size(N - 1)}
    {
        buf_.literal = &data[0];
    }

    explicit basic_string(std::nullptr_t) = delete;

    explicit basic_string(pointer data)
      : basic_string{data, traits_type::length(data)}
    {}

    basic_string(pointer data, size_type len)
      : size_{make_external_size(len)}
    {
        const auto buf_size = (len + 1) * sizeof(char_type);
        const auto external =
            static_cast<external_buffer*>(malloc(sizeof(external_buffer) + buf_size));
        if (!external)
            throw std::bad_alloc();

        new (external) external_buffer{};
        memcpy(external_data(external), data, buf_size);

        buf_.external = external;
    }

    basic_string(const basic_string& other)
      : size_{other.size_}
    {
        copy(other);
    }

    basic_string& operator=(const basic_string& other)
    {
        release();
        copy(other);
        return *this;
    }

    template<size_type N>
    basic_string& operator=(value_type (&data)[N])
    {
        return (*this) = basic_string{data};
    }

    basic_string& operator=(std::nullptr_t) = delete;

    // TODO: Custom move constructor would be slightly more efficient, e.g. it
    //       does not have to increment then decrement the ref-count.

    // TODO: Move assignment operator could be efficiently implemented using
    //       swap, which we need anyway.

    ~basic_string()
    {
        release();
    }

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
        return c_str();
    }

    constexpr const_pointer c_str() const noexcept
    {
        if (has_external_buffer())
            return external_data();
        return buf_.literal;
    }

    constexpr operator std::basic_string_view<CharT, Traits>() const noexcept
    {
        return {data(), size()};
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
        return size_ >> 1;
    }

public: // Operations
    constexpr int compare(const basic_string& rhs) const noexcept
    {
        // TODO: Since we know the length of both strings, we can do better than
        // this.
        return compare(rhs.data());
    }

    constexpr int compare(pointer rhs) const noexcept
    {
        const auto lhs = data();
        if (lhs == rhs)
            return 0;
        // TODO: This is only valid for basic_string<char>
        return strcmp(lhs, rhs);
    }

private:
    constexpr char_type* external_data() const noexcept
    {
        return external_data(buf_.external);
    }

    static constexpr char_type* external_data(external_buffer* external) noexcept
    {
        return reinterpret_cast<char_type*>(reinterpret_cast<char*>(external) +
                                            sizeof(external_buffer));
    }

    static constexpr size_type make_literal_size(size_type n)
    {
        return (n << 1) | 0;
    }

    static constexpr size_type make_external_size(size_type n)
    {
        return (n << 1) | 1;
    }

    constexpr bool has_external_buffer() const noexcept
    {
        return (size_ & 1) != 0;
    }

    void copy(const basic_string& other) noexcept
    {
        if (other.has_external_buffer()) {
            buf_.external = other.buf_.external;
            buf_.external->ref_count.fetch_add(1);
        } else {
            buf_.literal = other.buf_.literal;
        }
    }

    void release() noexcept
    {
        if (has_external_buffer()) {
            const auto refs = buf_.external->ref_count.fetch_sub(1) - 1;
            if (refs == 0) {
                buf_.external->~external_buffer();
                free(buf_.external);
            }
        }
    }
};

template<typename CharT, typename Traits>
inline std::ostream& operator<<(std::ostream& os, const basic_string<CharT, Traits>& s)
{
    return os << s.c_str();
}

#ifdef IMMUTABLE_HAS_SPACESHIP
template<class CharT, class Traits>
inline constexpr auto operator<=>(const basic_string<CharT, Traits>& lhs,
                                  const std::basic_string<CharT, Traits>& rhs) noexcept
{
    const auto order = lhs.compare(rhs);
    if (order < 0) {
        return std::strong_ordering::less;
    } else if (order == 0) {
        return std::strong_ordering::equal;
    } else if (order > 0) {
        return std::strong_ordering::greater;
    }
}
#else
#    define IMMUTABLE_DEFINE_COMPARISON_OPERATOR(op)                                               \
        template<class CharT, class Traits>                                                        \
        inline constexpr bool operator op(const basic_string<CharT, Traits>& lhs,                  \
                                          const basic_string<CharT, Traits>& rhs) noexcept         \
        {                                                                                          \
            return lhs.compare(rhs) op 0;                                                          \
        }                                                                                          \
                                                                                                   \
        template<class CharT, class Traits>                                                        \
        inline constexpr bool operator op(const basic_string<CharT, Traits>& lhs,                  \
                                          const CharT* rhs) noexcept                               \
        {                                                                                          \
            return lhs.compare(rhs) op 0;                                                          \
        }

IMMUTABLE_DEFINE_COMPARISON_OPERATOR(==)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(!=)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(<)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(<=)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(>)
IMMUTABLE_DEFINE_COMPARISON_OPERATOR(>=)
#endif // IMMUTABLE_HAS_SPACESHIP

#undef IMMUTABLE_DEFINE_COMPARISON_OPERATOR

} // namespace v1
} // namespace immutable

#undef IMMUTABLE_HAS_SPACESHIP

#endif // !defined(IMMUTABLE_BASIC_STRING_HPP)
