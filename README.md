# Immutable string

In some code bases strings are (1) often created from string literals, (2) never
modified after being created, and (3) copied multiple times. For code bases like
that, `std::string` is actually sub-optimal. Creating an `std::string` from a 
literal _must_ heap-allocate a copy because `std::string` is mutable. When you
copy an `std::string` object another heap-allocation has to be made because the
standard does not allow `std::string` to use copy-on-write semantics. 

If you  don't need the mutability, this library provides a better option: an 
immutable string with (mostly) the same interface as `std::string`. 

Since individual characters are immutable, string literals can be referenced 
instead of copied:

```c++
#include <ist/string.hpp>
#include <iostream>

int main()
{
    // you _must_ use the user-defined literal to avoid memory allocation
    using namespace ist::literals;
    // no memory allocated by ist::string here
    const auto s = "hello"_is;
    std::cout << s << '\n;
}
```

Similarly copying a string object just bumps the reference count on the
allocated buffer:

```c++
#include <ist/string.hpp>
#include <iostream>

int main()
{
    const ist::string s1 = "hello, world";
    // no additional memory allocated by ist::string here
    const ist::string s2 = s1;
    std::cout << s2 << '\n;
}
```

Even though you cannot modify the string, e.g. change individual characters or 
the length of the string, you _can_ still assign a new value to immutable string
objects:

```c++
#include <ist/string.hpp>
#include <iostream>

int main()
{
    using namespace ist::literals;
    auto s = "hello"_is;
    s = "goodbye";
    std::cout << s << '\n;
}
```
