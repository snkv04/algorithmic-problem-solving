#include <iostream>
#include <fstream>
#include <cassert>

int main() {
    // use the RAII classes for file handling in C++, so no need for fopen() and fclose() like in C

    // creates/writes to file
    // NOTE: does not open in "append" mode! overwrites, unless you pass in some flag in std::ios.
    std::ofstream fout("data.txt");
    fout << "hello" << '!';  // no guarantee that it flushed yet
    fout << std::endl;  // now buffer is flushed, should be safe to open ifstream
    for (int i = 0; i < 2; ++i) {
        fout << i << ' ' << static_cast<char>('a' + i) << std::endl;
    }

    // reads from file
    // can check if it exists by casting the stream's state to a boolean
    std::ifstream fin("data.txt");
    assert(fin);
    std::ifstream fin2("asdf.txt");
    assert(!fin2);

    // can read either lines or tokens =========================
    // can oneshot the whole line
    std::string s; int num; char ch;
    assert(getline(fin, s));  // reads line, and consumes newline character
    assert(s == "hello!");
    assert(getline(fin, s));  // reads separate tokens as one line, and consumes newline
    assert(s == "0 a");

    // can read tokens separately
    assert(fin >> num);  // reads next token, but does not consume TRAILING whitespace
    assert(num == 1);
    assert(fin >> ch);  // same
    assert(ch == 'b');
    assert(getline(fin, s));  // reads line, with nothing in it, and consumes newline
    assert(s == "");

    // at end of file, when no more characters remaining,
    // both operations return lvalue reference to stream in failed state,
    // so stream is interpreted as false
    assert(!getline(fin, s));
    assert(!(fin >> ch));
    // =========================================================

    return 0;
}
