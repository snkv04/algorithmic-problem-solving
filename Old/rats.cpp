#include <iostream>
#include <unordered_set>

using namespace std;

bool check(string &s) {
    int n = s.size();
    if (s.size() >= 8 && s.substr(0, 4).compare("1233") == 0 && s.substr(s.size()-4, 4).compare("4444") == 0) {
        for (int i = 3; i < s.size() - 4; ++i) {
            if (s[i] != '3') {
                return false;
            }
        }
        return true;
    }
    if (s.size() >= 8 && s.substr(0, 4).compare("5566") == 0 && s.substr(s.size() - 4, 4).compare("7777") == 0) {
        for (int i = 3; i < s.size() - 4; ++i) {
            if (s[i] != '6') {
                return false;
            }
        }
        return true;
    }
    return false;
}

string rats(string &s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    string result(s.size()+1, ' ');
    int carry = 0;
    for (int i = s.size(); i >= 0; --i) {
        int val, a, b;
        if (i > 0) {
            a = s[i-1] - '0'; b = rev[i-1] - '0';
        } else {
            a = 0; b = 0;
        }
        val = a + b + carry;
        carry = val / 10;
        val = val % 10;
        result[i] = (char) (val + '0');
    }

    sort(result.begin(), result.end());
    int nonzero = -1;
    for (int i = 0; i < result.size(); ++i) {
        if (result[i] != '0') {
            nonzero = i;
            break;
        }
    }
    result = result.substr(nonzero, result.size()-nonzero);

    return result;
}

void solve() {
    int k, m;
    string seq;
    cin >> k >> m >> seq;
    if (check(seq)) {
        cout << k << " C 1" << '\n';
        return;
    }

    unordered_set<string> seen;
    seen.insert(seq);
    for (int i = 2; i <= m; ++i) {
        seq = rats(seq);
        if (check(seq)) {
            cout << k << " C " << i << '\n';
            return;
        }
        if (seen.find(seq) != seen.end()) {
            cout << k << " R " << i << '\n';
            return;
        }
        seen.insert(seq);
    }
    cout << k << " " << seq << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p;
    cin >> p;
    while (p--) {
        solve();
    }

    return 0;
}