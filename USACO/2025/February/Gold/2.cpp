#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MOD = 1e9 + 7;

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

vector< array<int, 3> > get_segments(int n, int m) {
    map<int, int> delta;
    delta[n+1] = 0;
    while (m--) {
        int l, r;
        cin >> l >> r;
        delta[l] += 1;
        delta[r+1] -= 1;
    }

    int last = 0, curr = 0;
    vector<array<int, 3> > segments;
    for (auto entry : delta) {
        int newcurr = curr + entry.second;
        if (newcurr % 2 != curr % 2 || entry.first == n+1) {
            if (entry.first != 1) {
                array<int, 3> segment = {last+1, entry.first-1, curr % 2};
                segments.push_back(segment);
            }
            last = entry.first - 1;
        }
        curr = newcurr;
    }
    return segments;
}

ll modpow(ll base, ll exp) {
    if (exp == 0) return 1;

    if (exp % 2) {
        return (modpow(base, exp-1) * base) % MOD;
    } else {
        ll root = modpow(base, exp / 2);
        return (root * root) % MOD;
    }
}

ll modinv(ll num) {
    return modpow(num, MOD-2);
}

ll moddiv(ll a, ll b) {
    ll denom = modinv(b);
    return (a * denom) % MOD;
}

ll modshiftleft(ll num, ll shift) {
    return (num * modpow(2, shift)) % MOD;
}

// num should be divisible by 2**shift to avoid in modular division.
ll modshiftright(ll num, ll shift) {
    return moddiv(num, modpow(2, shift)) % MOD;
}

int main() {
    // reads in input, and compresses contiguous stretches of 0s and 1s into segments
    int n, m, q;
    cin >> n >> m >> q;
    vector< array<int, 3> > segments = get_segments(n, m);

    // precomputes prefix sums for counts of 1s, counts of 0s, and binary representations for suffixes
    int numseg = segments.size();
    vector<ll> pref1(numseg, 0), pref0(numseg, 0);
    for (int i = 0; i < numseg; ++i) {
        pref1[i] = (i == 0 ? 0 : pref1[i-1]) + (segments[i][2] == 0 ? 0 : (segments[i][1] - segments[i][0] + 1));
        pref0[i] = (i == 0 ? 0 : pref0[i-1]) + (segments[i][2] == 1 ? 0 : (segments[i][1] - segments[i][0] + 1));
    }
    vector<ll> sufbinary(numseg, 0);
    for (int i = numseg-1; i >= 0; --i) {
        ll next = i == numseg - 1 ? 0 : sufbinary[i+1];
        ll currnoshift = segments[i][2] == 0 ? 0 : (modpow(2, segments[i][1] - segments[i][0] + 1) - 1);
        ll curr = modshiftleft(currnoshift, n - segments[i][1]);
        sufbinary[i] = (curr + next) % MOD;
    }

    // loops through queries
    while (q--) {
        // reads in inputs
        int l, r, k;
        cin >> l >> r >> k;

        // finds which of the existing segments l and r fall into
        auto findidx = [&](int x) {
            int lo = 0, hi = numseg-1;
            while (true) {
                int mid = (lo+hi)/2;
                if (segments[mid][1] < x) {
                    lo = mid + 1;
                } else if (segments[mid][0] > x) {
                    hi = mid - 1;
                } else {
                    return mid;
                }
            }
        };
        int lidx = findidx(l), ridx = findidx(r);

        // deals with the case where they're both in the same segment
        if (lidx == ridx) {
            if (segments[lidx][2] == 0) {
                cout << "0\n";
            } else {
                ll result = modpow(2, k);
                cout << result - 1 << '\n';
            }
            continue;
        }

        // at least 1 "0" and at least 1 "1" within [l, r]
        // checks if we have enough 1s to fill a string of length k
        auto getcount = [&](int left, int right, int val) {
            int leftidx = findidx(left), rightidx = findidx(right);
            if (leftidx == rightidx) {
                if (val == segments[leftidx][2]) {
                    return right - left + 1;
                } else {
                    return 0;
                }
            }

            vector<ll> &pref = val == 0 ? pref0 : pref1;
            int leftblock = segments[leftidx][2] == val ? (segments[leftidx][1] - left + 1) : 0;
            int rightblock = segments[rightidx][2] == val ? (right - segments[rightidx][0] + 1) : 0;
            int middle = pref[rightidx-1] - pref[leftidx];
            return leftblock + middle + rightblock;
        };
        int num1s = getcount(l, r, 1);
        if (num1s >= k) {
            ll result = modpow(2, k);
            cout << result - 1 << '\n';
            continue;
        }

        // checks if we don't have any 1s at all
        if (num1s == 0) {
            cout << "0\n";
            continue;
        }

        // have some 1s, which we will use, but also need to use some 0s; fill in 0s from right
        // basically, we want to use as few segments as possible (on the right side) to gather the necessary 0s
        int needed0s = k - num1s;
        int lo = 0, hi = ridx, leftbound = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int available0s = getcount(segments[mid][0], r, 0);
            if (available0s >= needed0s) {
                leftbound = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        assert(segments[leftbound][2] == 0);
        int used1s = getcount(segments[leftbound][0], r, 1);
        int usedchars = needed0s + used1s;
        int rem1s = k - usedchars;

        /*
        - dividing A by B in a modular field, when A % B != 0, can be buggy and give incorrect answers.
        if we are trying to truncate the remainder, then just subtract it first, and then divide.
        in the context of this problem, we want to right-shift a binary number in a modular field,
        but we do that right-shifting by performing division modulo 1e9+7, so we should subtract out
        the part that gets truncated during the shift first.
        */
        // constructs the binary representation of the string in 2 parts: the right side part, which
        // consists of both 0s and 1s, and the left side part, which justs uses 1s until the string of
        // length k is complete
        ll preshift = sufbinary[leftbound];
        if (ridx != numseg-1) {
            // subtracts out most of the part that gets truncated during the shift
            preshift = (preshift - sufbinary[ridx+1] + MOD) % MOD;
        }
        if (segments[ridx][2] == 1 && segments[ridx][1] > r) {
            // subtracts out the rest of the part that gets truncated during the shift
            ll ones = segments[ridx][1] - r;
            ll subtracting = modshiftleft(modpow(2, ones) - 1, n - segments[ridx][1]);
            preshift = (preshift - subtracting + MOD) % MOD;
        }
        ll result = modshiftright(preshift, n - r);
        if (usedchars < k) {
            // fill in remaining chars on left with 1s
            ll val = modshiftleft(modpow(2, rem1s) - 1, usedchars);
            result = (result + val) % MOD;
        }
        cout << result << '\n';
    }
}
