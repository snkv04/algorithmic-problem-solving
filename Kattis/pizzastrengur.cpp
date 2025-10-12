#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /*
    - the reasoning behind why we use a randomly-selected letter is that if we always choose letters in
    the same order (e.g., "P -> I -> Z -> A"), then the string AAA...AAA exploits this order, so even
    though the expected value across all strings for number of guesses we need for each letter is 2.25
    ((1 + 2 + 3 + 3) / 4), they can construct a worst-case string to exploit our algorithm and make it
    take 3 guesses per letter. however, by randomly selecting the next letter to guess, no string can
    exploit our order of guesses, so there are then no best/worst cases, and any given string should
    expect to be guessed in 2.25n guesses. basically, we're moving from taking the expectation across
    all input strings to taking the expectation across all randomly-generated sequences of letters to
    guess, so that's why the average number of guesses is the same but the inputs can't force a worst
    case (because they now don't have control over the thing that varies).
    */

    int n;
    cin >> n;

    mt19937 rng;

    string s(n, ' ');
    for (int i = 0; i < n; ++i) {
        vector<char> letters = {'P', 'I', 'Z', 'A'};
        for (int j = 0; j < 3; ++j) {
            int idx = uniform_int_distribution<int>(0, letters.size() - 1)(rng);
            char letter = letters[idx];
            letters.erase(letters.begin() + idx, letters.begin() + idx + 1);

            s[i] = letter;
            cout << s.substr(0, i + 1) << endl;
            int res;
            cin >> res;
            if (res == 2) {
                return;
            } else if (res == 1) {
                break;
            } else {
                if (j == 2) s[i] = letters[0];
            }
        }
    }
    cout << s << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
