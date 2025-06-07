#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
map<string, int> mem;
int absbest;

template <typename Container>
string print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    stringstream ss;
    ss << prefix << "[";
    for (const auto &elem : c) {
        ss << elem << ",";
    }
    ss << "]";
    return ss.str();
}

ll sqrt(ll n) {
    // calculates the floor of sqrt(n) in O(log(n))
    if (n == 0) return 0;
    else if (n < 0) return -1;
    ll l = 1, r = n, sqrt = -1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll factor = n / mid;
        if (mid <= factor) {
            sqrt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return sqrt;
}

vector<int> prime_factorization(int n) {
    vector<int> factors;
    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            n /= i;
            factors.push_back(i);
        }
    }
    if (n != 1) {
        factors.push_back(n);
    }
    return factors;
}

int gcd(int a, int b) {
    int A = max(a, b), B = min(a, b);
    while (B != 0) {
        int r = A % B;
        A = B;
        B = r;
    }
    return A;
}

string repr(int idx, vector<int> &groups) {
    stringstream ss;
    ss << idx << ";";
    ss << print_container(groups);
    return ss.str();
}

int recurse(int idx, vector<int> &primes, vector<int> &groups, int k) {
    string str = repr(idx, groups);
    // cout << "str = " << str << "\n";
    if (idx == primes.size()) {
        absbest = min(absbest, (int) groups.size());
        return (int) groups.size();
    }
    if (mem.find(str) != mem.end()) {
        // cout << "found in mem for str = " << str<<endl;
        absbest = min(absbest, mem[str]);
        return mem[str];
    }
    if (groups.size() >= absbest) return 1e9;

    int best = 1e9;
    int p = primes[idx];
    for (int i = 0; i < groups.size(); ++i) {
        if (k / groups[i] >= p) {
            groups[i] *= p;
            best = min(best, recurse(idx+1, primes, groups, k));
            groups[i] /= p;
        }
    }

    groups.push_back(p);
    best = min(best, recurse(idx+1, primes, groups, k));
    groups.pop_back();
    mem[str] = best;
    absbest = min(absbest, best);
    return best;
}

void solve() {
    /*
    basically, in an operation we can either set x to a multiple of itself
    or divide it by a factor of itself, and we want to transform x into y
    with each factor (for either multiplication or division) being less than
    or equal to some bound using the minimum number of operations.
    first of all, since multiplication and division are commutative with each
    other IF we're applying them all onto the accumulated result, then we can
    start off with only multiplication and then do all our divisions. in other
    words, we start with x, do some multiplications to end up at some large value,
    and then do a bunch of divisions to end up at y. if there was no bound k,
    then this would always be achievable in at most 2 operations by first
    multiplying x by y and then dividing by x to get y.
    also, note that x and y might share some factors. if that's the case, then
    it's unnecessary to multiply or divide our accumulator (which is initialized
    to x) by any multiple of a shared factor among x and y. so, we can divide
    both x and y by gcd(x, y), so then x and y will be coprime and share absolutely
    no factors.
    now, with this simplified representation of the problem, this means that we
    can start with x, go up to xy (the product of x and y), and then divide down
    to y. why xy? because, if x and y are coprime, then xy is equal to lcm(x, y).
    in other words, we multiply x by y and then divide by x.
    in order to do this, we can first identify that the smallest, indivisible
    factors of x (or y) are the prime factors. the same process will be done for
    both x and y, since multiplication and division are effectively the same operation
    but inverses of one another, so let's just take a look at one. if any of the prime
    factors of either of these numbers are greater than k, then we can't multiply (or
    divide) by that number, meaning that we can't perform the necessary operations to
    get x to xy or to get from xy to y, so then it's impossible. otherwise, each operation
    can potentially group up multiple prime factors into their product and use that as the
    "a" in the operation, so the problem morphs into the following: given a multiset of
    prime factors, group them up into some number of groups such that the product of each
    group is <= k and such that the number of groups is minimum. the answer is just the
    output of this after running it on x and y separately and then adding those two
    outputs together.
    to solve this simplified problem, we can use an almost standard recursive approach,
    and then implement memoization on it. just fix the order of the factors, and then
    actually construct the groups. the groups can actually just be represented by their
    products, since that's the only property of them that we care about for this particular
    problem here. now, we can just iterate over the factors themselves, and for each,
    select which group we want to place that factor into or make a new group using only
    that factor. for memoization, the only things that change between each call of the
    recursive function are the index of the factor currently being considered and the
    products of the groups, so those two things can be serialized into the key used for
    memoization.

    simplified way of coming up with this backtracking solution?
    draw out the decision tree. that's literally it. just visualize my thoughts and
    make an algorithm out of them.

    what can be taken from this problem?
    when there's a subproblem for a problem, just formulate it in a simple and clear
    way, then put full focus and effort into solving it in order to streamline how i
    spend my time solving the problem.
    */

    // int x, y, k;
    // cin >> x >> y >> k;
    // // print_container(prime_factorization(y), "prime factorization = ");

    // int g = gcd(x, y);
    // x /= g;
    // y /= g;
    // vector<int> px = prime_factorization(x), py = prime_factorization(y);
    // // cout << "px = " << print_container(px) << "\n";
    // // cout << "py = " << print_container(py) << "\n";
    // int mx = 0;
    // for (int pxi : px) mx = max(mx, pxi);
    // for (int pyi : py) mx = max(mx, pyi);
    // if (mx > k) {
    //     cout << "-1\n";
    //     return;
    // }
    
    // int ans = 0;
    // for (vector<int> vec : vector<vector<int>>({px, py})) {
    //     absbest = 1e9;
    //     vector<int> groups;
    //     mem.clear();
    //     int val = recurse(0, vec, groups, k);
    //     ans += val;
    // }
    // cout << ans << "\n";

    /*
    alternate solution:
    we perform the same simplifications on the problem as before, and we arrive at the problem
    of performing as few operations as possible both to get a total product of x and a total
    product of y. now, the previous way of formulating the problem was to say that we have some
    prime factors (such as of x) and we want to group them up such that each group's product
    was leq k and the total number of groups is minimum. another way of viewing the problem is:
    for a given number, we want to find the minimum number of factors we can break it down into
    such that each factor is <= k and the product of them is equal to that given number, and then
    we can find that value for x and y. this is almost identical to the coin combinations problem,
    where a number i can be made by looking through each factor j of i and setting mem[i] equal
    to min(mem[i], mem[i/j]+1) if j <= k. intuitively, the subproblem of mem[i/j] takes into
    consideration all of the other factors, and the last factor is dealt with through the operation
    that goes from i/j to i. now, we can't directly do this, since it'll be O(x^2 + y^2), so instead,
    we can make the astute observation that the only values in the table that actually matter
    are those indexed by divisors of x (when we're running it for x), and this drastically reduces
    the number of elements that we care about. (the number of divisors for a number, calculated
    across the highly composite numbers, can actually be approximated by f(n) = cbrt(n).) then, we
    just run it for both x and y separately, since x and y will have different divisors (especially
    if we make them coprime), and we can get our answer.

    how could i come up with this on my own?
    well, let's try connecting it to what we already know. in what way is this connected to the
    other formulation of the problem? in the original way, we specifically want to find the min
    groups for those two values (x and y), while in this way, we use the traditional DP formulation
    where we can look up the memoized results for any number and we want to find the results
    specifically for x and y. well, it's a little more nuanced than that, since for each of x and y,
    we do it separately, as we only want to calculate the DP table across the divisors of the final
    number we care about. still, basically, in the first solution we iterate over the factors (or
    the "elements" or "items" that we can use), while in the second solution we iterate over the
    numerical values of the thing that we are trying to compute something else for. in the first,
    the final output draws on having used all of the items that we need to use, while in the
    second, the final output draws on having computed the answer for many smaller values of input;
    the subproblems are conceptually different.

    generalizable ideas?
    when computing the DP table, only a select few indices will be "filled in" (in the implementation,
    the table only includes those cells). the ones that'll be filled in can be precomputed.
    */

    int x, y, k;
    cin >> x >> y >> k;
    int g = gcd(x, y);
    x /= g; y /= g;

    vector<int> factorx, factory;
    for (int i = 1, sqrtx = (int) sqrt(x); i <= sqrtx; ++i) {
        if (x % i == 0) {
            factorx.push_back(i);
            if (i * i != x) {
                factorx.push_back(x / i);
            }
        }
    }
    for (int i = 1, sqrty = (int) sqrt(y); i <= sqrty; ++i) {
        if (y % i == 0) {
            factory.push_back(i);
            if (i * i != y) {
                factory.push_back(y / i);
            }
        }
    }
    sort(factorx.begin(), factorx.end());
    sort(factory.begin(), factory.end());
    // cout << "x = " << x << "\n";
    // cout << print_container(factorx, "factorx = ") << "\n";
    // cout << "y = " << y << "\n";
    // cout << print_container(factory, "factory = ") << "\n";

    int ans = 0;
    for (pair<int, vector<int>> p : vector<pair<int, vector<int>>>({
        make_pair(x, factorx),
        make_pair(y, factory)
    })) {
        int num = p.first;
        vector<int> factors = p.second;
        vector<int> mem(num+1, 1e9); // mem[i] = min number of ops to construct i
        mem[1] = 0;
        for (int i = 1; i < factors.size(); ++i) {
            int factor = factors[i];
            for (int j = 0; j <= i; ++j) {
                int prev = factors[j];
                // cout<<"factor="<<factor<<", prev="<<prev<<"\n";
                if (prev > k) break;
                if (factor % prev == 0) {
                    mem[factor] = min(mem[factor], mem[factor/prev] + 1);
                }
            }
        }

        // cout << print_container(mem, "mem = ")<<"\n";
        if (mem[num] == 1e9) {
            cout << "-1\n";
            return;
        } else {
            ans += mem[num];
        }
    }
    cout << ans << "\n";
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
