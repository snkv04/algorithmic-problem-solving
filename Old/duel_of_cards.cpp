#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    set<int> st;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        st.insert(x);
    }

    set<int> other, other2;
    for (int i = 1; i <= 2*n; ++i) {
        if (st.find(i) == st.end()) {
            other.insert(i);
            other2.insert(i);
        }
    }

    int mn = n, mx = 0;
    for (const auto &card : st) {
        if (other.upper_bound(card) != other.end()) {
            other.erase(other.upper_bound(card));
            mn--;
        } else {
            break;
        }
    }
    for (set<int>::reverse_iterator it = st.rbegin(); it != st.rend(); ++it) {
        int card = *it;
        if (--(other2.upper_bound(card)) != --(other2.begin())) {
            other2.erase(--other2.upper_bound(card));
            mx++;
        } else {
            break;
        }
    }
    cout << mn << " " << mx << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}