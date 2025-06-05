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
    /*
    realistic thought process (since i partially started it, looked at some of the solution while looking
    for something else, then continued it):
    so we have that we want to find an x, y, z such that xw+yd+0z=p and x+y+z=n. this is the same as finding
    some x and y such that x+y<=n and xw+yd=p, because z can easily be found as n-x-y if those two conditions
    are met. what other information do we have? it's a standard result that this is only possible if gcd(x, y)
    divides p, but it turns out that this isn't useful since both x and y have to be positive. what else can
    we do? well, based on the constraints of w compared to the other values, maybe we can do an O(w) or
    O(w * log(something)) solution. since the only unfixed values are x and y, maybe we can iterate over the
    values for one of them? if we were to iterate over the values of x such as from 1 to w, then in the last
    iteration, we have xw = w^2, which is hard to find some useful information in. however, if we iterate over
    y from 1 to w, then the max value is yd=wd, and this is equivalent to if we have x=d so then xw=dw. this
    means that we can swap out some amount of wins for some number of draws (and actually we can probably scale
    it down so that instead of swapping out some points equalling the product wd, we swap out some points
    equalling the value of lcm(w, d) between wins and draws). this connects to another piece of information:
    we want x+y<=n, so ideally, we keep x and y as small as possible, and one way to do this is to swap out
    some number of draws for wins instead (since d < w, so the number of draws would be less than the number
    of wins to get the same number of points). based on this, the reason why we don't need to iterate the
    value of y past w is because if we have a y>w, then the first w draws can be converted into some smaller
    number of wins (meaning we subtract some amount from y and add some smaller amount to x), resulting in a
    higher likelihood that we end up with some x and y such that x+y<=n. so, we can restrict y to be in [0, w),
    as any more than that and we can just replace a portion of y with an addition to x, which is reminiscent
    of the standard integer division formula a=qb+r, since r is restricted to be in [0, b) and so q is made
    as large as needed in order to ensure that r meets that constraint. also, the reason why this wouldn't
    work for iterating over x is that even though we do only need to iterate up to d, the idea of "we only
    need to iterate up to d because any more wins and we can convert them to draws" is founded on an operation
    that increases the overall sum of x and y, which makes that sum less likely to be less than or equal to n.
    in short, we iterate y from 0 through w, and for each, we find if there is an x (from which we can
    deterministically state if there's a z) for which the conditions hold.
    */

    ll n, p, w, d;
    cin >> n >> p >> w >> d;
    for (ll y = 0; y <= min(n, w); ++y) {
        ll remaining = p - y * d;
        if (remaining >= 0 && remaining % w == 0) {
            ll x = remaining / w;
            if (x + y <= n) {
                cout << x << " " << y << " " << (n - x - y) << "\n";
                return;
            }
        } else if (remaining < 0) {
            break;
        }
    }
    cout << "-1\n";
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
