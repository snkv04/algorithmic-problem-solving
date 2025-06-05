#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void solve() {
    int n, q;
    cin >> n >> q;
    unordered_map<int, int> idx;
    int p[n];
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        idx[p[i]] = i;
    }

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        --l; --r;
        if (idx[k] > r || idx[k] < l) {
            cout << "-1 ";
            continue;
        }

        // the only part of an element that matters is if it is less than or greater
        // than k
        int m = (l + r) / 2;
        int correctless = 0, correctgreater = 0, incorrectless = 0, incorrectgreater = 0;
        int countleft = 0, countright = 0;
        while (p[m] != k) {
            bool toright = idx[k] > m;

            if (toright) {
                if (k > p[m]) ++correctless;
                else ++incorrectgreater;
            } else {
                if (k < p[m]) ++correctgreater;
                else ++incorrectless;
            }
            
            if (toright) {
                l = m+1;
            } else {
                r = m-1;
            }
            m = (l + r) / 2;
        }
        // cout << "p[" << m << "] = " << k << endl;

        // some elements must be changed (the ones that point in the incorrect direction),
        // so we can use the elements of the opposite type (less vs. greater than k) that
        // also need to be changed, and if those aren't enough, then we check if we have
        // enough remaining elements to use
        // incorrectless counts the number of elements that should be swapped out for elements
        // that are greater than k
        // what we're basically doing is first checking if there are enough to properly fill
        // in both sides, and if both of those checks pass, then actually moving on to calculating
        // the number that we need
        int totalgreater = n-k, totalless = k-1;
        if ((incorrectgreater > incorrectless
                && incorrectgreater - incorrectless > totalless - correctless - incorrectless)
                || (incorrectless > incorrectgreater
                && incorrectless - incorrectgreater > totalgreater - correctgreater - incorrectgreater)) {
            cout << "-1 ";
        } else {
            int mn = min(incorrectgreater, incorrectless), mx = max(incorrectgreater, incorrectless);
            cout << 2 * mn + 2 * (mx - mn) << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
