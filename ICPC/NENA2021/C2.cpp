#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    for (int start = 0; start >= -6; --start) {
        bool works = true;
        for (int i = start; i < n && works; i += 7) {
            set<char> st;
            int cnt = 0;
            for (int j = i; j < i+7; ++j) {
                if (j >= 0 && j < n) {
                    st.insert(s[j]);
                    ++cnt;
                }
            }
            if (st.size() != cnt) {
                works = false;
                break;
            }
        }
        if (works) {
            cout << "1\n";
            return;
        }
    }
    cout << "0\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}