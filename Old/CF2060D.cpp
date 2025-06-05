#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
ll fac[500005];

ll pow(ll base, ll exp, ll mod) {
    if (exp == 0) return 1LL;
    ll result = pow(base, exp/2, mod);
    result *= result; result %= mod;

    if (exp%2) {
        return (result * base) % mod;
    } else {
        return result;
    }
}

ll modInverse(ll a, ll mod) {
    return pow(a, mod-2, mod);
}

ll div(ll a, ll b, ll mod) {
    ll inv = modInverse(b, mod);
    return ((a % mod) * inv) % mod;
}

void solve() {
    /*
    what's the problem, simplified?
    given a list of letter frequencies, where there are less than or equal to 26 letters and the
    sum of the frequencies is leq 5e5, let an ordering be defined as first splitting the letters
    into two subsets so that the sum of frequencies of letters in the first subset is equal to
    the floor of half of the total sum of frequencies and that of the second subset is equal to
    the ceiling, and afterward ordering the letters in both subsets separately in their own
    slots independently. we want to find the total number of orderings.

    what's the solution?
    the obvious, straightforward solution is to go through all subsets of letters, and for each,
    we set the subset equal to the first group and the complement equal to the second group, and
    if the frequency sums meet the conditions, then calculate the number of orderings for each subset
    independently and multiply them together (since the orderings are independent of each other).
    to calculate the orderings for a given subset, we can use the multinomial formula: it's the
    factorial of the sum of frequencies divided by the product of the factorials of each frequency
    value.
    to compute this efficiently, first recognize that for any given splitting of letters into the
    first and second groups, the number of ways to order the actual letters in their slots once that
    splitting is determined is a constant number. this is because the product of the number of ways
    to order all of the letters in the first group and the number of ways for the second group is
    a constant term that can be computed straight from the values given in the problem. then, the
    problem just comes down to finding the number of ways to get a subset of the letters whose
    frequencies sum up to the floor of half of the sum of frequencies (which is actually equal to the
    number of subsets whose frequencies sum up to the ceiling, since for any given subset, the
    complement subset of items not chosen will have the complement size, so given that the floor and
    ceiling of half are complement sizes, the number of subsets whose sums equal each will be the
    same). this is a standard problem that is solvable with dynamic programming.
    
    what are the parts of the solution that i couldn't come to on my own that i should internalize?
    what i was trying to do what split up the algorithm into first splitting the letters into two
        groups and then trying to compute the number of orders after taking that splitting of letters
        into consideration. what i should have done is find the invariant (the orderings), and then
        focused on computing the subsets. basically, we can separate out the subset step and the
        ordering step into two parts that are merged together at the end through a simple multiplication
        instead of finding all the orderings for each valid subset that goes into the even-indexed
        spots.

    what are some problem-solving techniques to take away?
    write out the equations/formulas. this might help with identifying some invariants or interesting
        properties that i couldn't see while visualizing them in my head

    what are some math(/DS?)/algo concepts that i should take away?
    if there are factorials used anywhere, precompute them all.
    */

    vector<int> c;
    int n, s = 0;
    for (int i = 0; i < 26; ++i) {
        int ci;
        cin >> ci;
        if (ci) {
            c.push_back(ci);
            s += ci;
        }
    }
    n = c.size();

    vector<ll> mem(s+1, 0);
    mem[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = s; j >= 1; --j) {
            if (j - c[i] >= 0) {
                mem[j] = (mem[j] + mem[j-c[i]]) % MOD;
            } else {
                break;
            }
        }
    }

    ll num = (fac[s/2] * fac[(s+1)/2]) % MOD;
    ll denom = 1;
    for (int ci : c) denom = (denom * fac[ci]) % MOD;
    ll ans = (div(num, denom, MOD) * mem[s/2]) % MOD;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i <= 500000; ++i) {
        if (i <= 1) fac[i] = 1;
        else {
            fac[i] = fac[i-1] * i;
            fac[i] %= MOD;
        }
    }

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
