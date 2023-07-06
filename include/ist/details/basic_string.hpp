// Copyright Teis Johansen 2021
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at http://boost.org/LICENSE_1_0.txt)
#ifndef ISTLIB_BASIC_STRING_HPP
#define ISTLIB_BASIC_STRING_HPP

#ifndef __cplusplus
#    error "This file is only meant for C++ compilers"
#endif // defined(__cplusplus)

#include <ist/details/basic_string_range.hpp>

#include <algorithm>
#include <atomic>
#include <cstring>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace ist {
inline namespace v1 {

namespace details {

/// Used by the user-defined literal prevent allocations for literals as opposed
/// to character arrays.
template<typename CharT>
struct basic_literal_string_ref {
    const CharT* data;
    size_t size;
};

using literal_string_ref = basic_literal_string_ref<char>;
using wliteral_string_reg = basic_literal_string_ref<wchar_t>;

} // namespace details

template<typename CharT, typename Traits>
class basic_string
  : public details::basic_string_range<CharT, Traits, basic_string<CharT, Traits>> {
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
    using char_type = CharT;

    struct external_buffer {
        std::atomic_size_t ref_count{1};
    };

    union buffer {
        value_type* literal;
        external_buffer* external;
    };

    static constexpr value_type empty_literal_[1] = {};

    // TODO: We can also support SBO storage if we steal one byte of the size

    buffer buf_;
    size_type size_;

public: // Constructors
    constexpr basic_string() noexcept;
    constexpr explicit basic_string(details::basic_literal_string_ref<CharT> literal) noexcept;
    template<size_type N>
    explicit basic_string(value_type (&data)[N]) noexcept;
    explicit basic_string(std::nullptr_t) = delete;
    explicit basic_string(pointer data);
    basic_string(pointer data, size_type len);
    basic_string(const basic_string& other);

    basic_string& operator=(const basic_string& other);
    template<size_type N>
    basic_string& operator=(value_type (&data)[N]);
    basic_string& operator=(std::nullptr_t) = delete;

    // TODO: Custom move constructor would be slightly more efficient, e.g. it
    //       does not have to increment then decrement the ref-count.

    // TODO: Move assignment operator could be efficiently implemented using
    //       swap, which we need anyway.

    ~basic_string();

public: // Element access
    constexpr const_pointer c_str() const noexcept;

private:
    constexpr char_type* external_data() const noexcept;
    static constexpr char_type* external_data(external_buffer* external) noexcept;
    static constexpr size_type make_literal_size(size_type n);
    static constexpr size_type make_external_size(size_type n);
    constexpr bool has_external_buffer() const noexcept;
    static external_buffer* make_external_buf(pointer data, size_type len);
    void copy(const basic_string& other) noexcept;
    void release() noexcept;

public: // basic_string_range
    //friend base_type;
    constexpr const_pointer get_data() const noexcept;
    constexpr size_type get_size() const noexcept;
};

} // namespace v1
} // namespace ist


#if __cpp_nontype_template_args < 201911

namespace ist {
inline namespace v1 {
namespace literals {

template<typename CharT>
basic_string<CharT> operator""_is(const CharT* str, std::size_t len);

} // namespace literals
} // namespace v1
} // namespace ist

#else // if compiler supports non-type template args

#    include <ist/details/literal_string.hpp>

namespace ist {
inline namespace v1 {
namespace literals {

template<details::literal_string Literal>
constexpr string operator""_is();

} // namespace literals
} // namespace v1
} // namespace ist

#endif // if compiler supports non-type template args

#endif // !defined(ISTLIB_BASIC_STRING_HPP)
