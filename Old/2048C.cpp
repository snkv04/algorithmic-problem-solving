#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

string exor(string &s, int l1, int r1, int l2, int r2) {
    if (r1 - l1 < r2 - l2) {
        swap(l1, l2);
        swap(r1, r2);
    }

    string result(r1 - l1 + 1, 'a');
    for (int i = 0; i <= r1-l1; ++i) {
        int first = s[r1-i] - '0', second = (r2 - i >= l2 ? s[r2-i] : '0') - '0';
        result[r1-l1-i] = '0' + (first ^ second);
    }

    return result;
}

bool cmp(string &bin1, string &bin2) {
    int size = max(bin1.size(), bin2.size());
    string b1 = bin1.size() < size ? (string(size - bin1.size(), '0') + bin1) : bin1;
    string b2 = bin2.size() < size ? (string(size - bin2.size(), '0') + bin2) : bin2;
    for (int i = 0; i < size; ++i) {
        if (b1[i] != b2[i]) {
            return b1[i] < b2[i];
        }
    }
    return false;
}

void solve() {
    string s;
    cin >> s;
    int length = s.size();
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            --length;
        } else {
            break;
        }
    }
    if (length == 0) {
        cout << "1 " << s.size() << " 1 1\n";
        return;
    }

    int bestl = -1, bestr = -1; string bestxor = "0";
    for (int i = 0; i <= s.size() - length; ++i) {
        int l = i, r = l + length -1;
        string result = exor(s, 0, s.size() - 1, l, r);
        if (cmp(bestxor, result)) {
            bestl = l;
            bestr = r;
            bestxor = result;
        }
    }

    cout << "1 " << s.size() << " " << bestl + 1 << " " << bestr + 1 << "\n";
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
