#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

vector<int> to_set(string s) {
    vector<int> v;
    for (int i = 0; i < 20; ++i) if (s[i] == '1') v.push_back(i + 1);
    return v;
}

string from_set(vector<int> v) {
    string s(20, '0');
    for (int v_i : v) s[v_i - 1] = '1';
    return s;
}

void solve(string s) {
    /*
    - notes:
        - if you only have a "data" and "checksum", and one of them is corrupted, then you don't know if the
        data are corrupted or the checksum is corrupted. so, you can instead have a checksum1 based on the data,
        and a checksum2 based on the checksum1. then, UNDER THE ASSUMPTION THAT ONLY ONE OF THE THREE ARE CORRUPTED,
        if checksum2 doesn't align with checksum1, then the data are fine. if it does align with checksum1, then
        checksum1 can be used in combination with data (the known, possibly-corrupted data) to get the correct
        value of data, regardless of if data was corrupted or not.
        - the fact that x \in [1, 2^15] means we can map it into x' \in [0, 2^15). this is obvious, but worth
        pointing out anyway, because it's a useful idea.
        - let all 3 of {data, checksum1, checksum2} be viewed as binary arrays. then, checksum1 is the XOR of the
        array indices where data is 1, while checksum2 is the XOR of the actual checksum1 array itself. how do
        you even think of that? well, start with the properties of a checksum: it is useful because it helps determine
        if something is wrong. if we want to know if there's something wrong between cs1 and cs2, then only storing
        the XOR of the binary values is enough, but if we know that cs1 and cs2 are fine, then cs1 actually needs to
        tell us where something is wrong.
            - basically, this is a hyper-specific problem where the conditions stated (e.g., only 1 bit will be
            flipped, we need exactly 2^4-1 bits to represent our number x, etc.) perfectly align to allow a very
            hyper-specific solution. very little to draw from other problems for this problem, and very little to
            draw from this problem for other problems. good for memorization of every detail, because maybe some
            details can be applied to other problems, but not good for learning, because there aren't many general
            patterns applied here.
        - the fact that x SPECIFICALLY has 15 bits is useful. why? that means that 4 bits are needed to represent
        all possible indices, where those indices will only lie in the interval [1, 15]. why can't we use the interval
        [0, 14]? because if, in the data array representing x, there is a 1 on index 0, then we'd XOR our checksum1
        with 0, which is the same as doing nothing if there is a 0 on index 0. so, the value 0 cannot be used as
        an index (for the purposes of building checksum1), and all other values (1 through 15, inclusive) are used,
        therefore using all possible values that 4 bits can represent.
    */

    if (s == "first") {
        int x;
        cin >> x;
        x -= 1;

        string data;
        for (int i = 1; i <= 15; ++i) {
            int bit = x % 2;
            x /= 2;
            data += (char) ('0' + bit);
        }

        int cs1 = 0;
        for (int i = 1; i <= 15; ++i) {
            if (data[i - 1] == '1') cs1 ^= i;
        }
        string checksum1;
        for (int i = 16; i <= 19; ++i) {
            int bit = cs1 % 2;
            cs1 /= 2;
            checksum1 += (char) ('0' + bit);
        }

        int cs2 = 0;
        for (int i = 16; i <= 19; ++i) if (checksum1[i - 16] == '1') cs2 ^= 1;
        char checksum2 = '0' + cs2;

        string res = data + checksum1 + checksum2;
        auto v = to_set(res);
        cout << v.size() << endl;
        for (int v_i : v) cout << v_i << ' ';
        cout << endl;
    } else {
        int n;
        cin >> n;
        vector<int> v(n);
        cin >> v;

        string str = from_set(v);
        string data = str.substr(0, 15), checksum1 = str.substr(15, 4), checksum2 = str.substr(19, 1);
        int d = 0; for (int i = 0; i < 15; ++i) if (data[i] == '1') d += 1 << i;
        int cs1 = 0; for (int i = 0; i < 4; ++i) if (checksum1[i] == '1') cs1 += 1 << i;
        int cs2 = checksum2[0] == '1';

        int actual_cs2 = 0; for (int i = 0; i < 4; ++i) if ((cs1 >> i) & 1) actual_cs2 ^= 1;
        int ans;
        if (cs2 != actual_cs2) {
            ans = d;
        } else {
            int actual_cs1 = 0;
            for (int i = 0; i < 15; ++i) if ((d >> i) & 1) actual_cs1 ^= i + 1;
            if (actual_cs1 == cs1) {
                ans = d;
            } else {
                int pos = actual_cs1 ^ cs1;
                d ^= (1 << (pos - 1));
                ans = d;
            }
        }
        ans += 1;
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int t = 1;
    cin >> t;
    while (t--) {
        solve(s);
    }

    return 0;
}
