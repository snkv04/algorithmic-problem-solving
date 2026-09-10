#include <bits/stdc++.h>
using namespace std;

string abbreviate(string word) {
    // If the number of characters in the word is equal to or less than 10,
    // then output is the same word
    // Else, then create a string that equals
    // "<first letter of word><total number of letters minus 2><last letter of word>"

    int characters = word.size();
    if (characters <= 10) {
        return word;
    } else {
        string first_letter = {word[0]};
        int middle_section = characters - 2;
        string last_letter = {word[characters - 1]};
        return first_letter + to_string(middle_section) + last_letter;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string word;
        cin >> word;
        string abbreviated = abbreviate(word);
        cout << abbreviated << endl;
    }

    return 0;
}
