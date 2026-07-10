#include <bits/stdc++.h>

int main() {
    // C-style strings: not a type, just a const char array,
    // where the null-terminator is a convention, not a requirement.
    // const is the convention because string literals should be immutable.
    // recall that sizeof(x) returns the size of x in bytes.
    const char* ptr = "hello";
    printf("sizeof(ptr[0]) = %zu\n", sizeof(ptr[0]));  // 1 byte: just a character
    printf("sizeof(ptr) = %zu\n", sizeof(ptr));  // 8 bytes: a pointer on a 64-bit architecture
    const char arr[] = "hello";
    printf("sizeof(arr[0]) = %zu\n", sizeof(arr[0]));  // 1 byte: just a character
    printf("sizeof(arr) = %zu\n", sizeof(arr));  // 6 bytes: 1 byte for each character, plus the null-terminator ('\0')

    // C++-style strings and standard functions
    std::string str = "this is some long string that most likely doesn't have SSO applied to it";  // if it did, then it'd live on the stack
    printf("sizeof(str) = %zu\n", sizeof(str));  // 24 bytes: 8 for heap address, 8 for size, 8 for capacity
    assert(str.size() == str.length() && str.size() == 72);
    assert(str.find("is") == 2);
    assert(str.rfind("is") == 5);
    assert(str.find("asdf") == std::string::npos && std::string::npos >= 0);
    assert(str.substr(13, 4) == "long");

    str.append("."); str += ".";  // O(1) amortized (specifically, amortized when accounting for reallocation)
    str = str + ".";  // O(n) due to immediate copy

    char* as_c_string = str.data();
    printf("str = |%s|\n", as_c_string);

    // stringstream, used mainly for tokenization
    std::stringstream stream;
    stream << "hello" << ' ' << "a b c";
    printf("stream.str().data() = |%s|\n", stream.str().data());
    std::string h, a, b, c;
    stream >> h >> a >> b >> c;
    printf("h = %s, a = %s, b = %s, c = %s\n", h.data(), a.data(), b.data(), c.data());

    // string_view is basically just used to allow non-owning (so no copies or moves needed) substrings of strings
    std::string_view view = str;
    assert(str.data() == view.data());  // same address
    std::string_view view_substr = view.substr(13, 4);
    assert(view_substr.data() == str.data() + 13);
    std::string str_substr = str.substr(13, 4);
    assert(str_substr.data() != view_substr.data());  // the copy, a result of calling substr(), was made elsewhere
    assert(str_substr == "long" && view_substr == "long");

    // std::basic_string is the underlying class.
    // std::string is just a specialized version of the class template std::basic_string; specifically,
    // std::string is a typedef of std::basic_string<char>.
    // think "using string = basic_string<char>;" inside the "std" namespace.
    // the only point of needing basic_string is to have strings with different (wider or narrower) char types.

    return 0;
}
