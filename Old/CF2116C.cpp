#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> memoized_gcds(5001, vector<int>(5001, 1e9));

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
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

int lookup_gcd(int a, int b, vector<vector<int>> &memoized_results) {
    int A = max(a, b), B = min(a, b);
    if (memoized_results[A][B] != 1e9) {
        return memoized_results[A][B];
    }

    int g;
    if (B != 0) {
        g = lookup_gcd(B, A % B, memoized_results);
    } else {
        g = A;
    }
    memoized_results[A][B] = g;
    return g;
}

void solve() {
    /*
    we can first start off with finding what the final value shared among the elements of the array
    will have to be. pretty clearly, it'll have to be the gcd of all the elements in the original
    array, and the reasoning is pretty simple so it won't be shown here. also, if we have that final
    value anywhere in the array, then all of the other elements will have it as a divisor so we can
    convert each of them one by one (since in one operation we can't change any more than one element)
    to that value using the existing one in a single operation. so, the process that we'll use is
    get a value to be equal to that final value as fast as possible (meaning in the fewest possible
    operations), and then move all of the other elements to be equal to that value.
    if there aren't any values in the array equal to that final value initially, how can we get a
    single value equal to it with the fewest operations? in the competition, i used a greedy algorithm
    that passed during the contest but actually fails tests after and isn't really correct. (a correct
    solution is below.) basically, i repeatedly do the following while there doesn't yet exist a value
    in the array that's equal to the gcd of all the elements: look through all pairs, keep track of
    whichever pair results in the lowest gcd, and perform an operation on that pair.
    */

    // int n;
    // cin >> n;
    // vector<int> a(n, 0); for (int i = 0; i < n; ++i) cin >> a[i];
    // int mn = a[0];
    // for (int i = 1; i < n; ++i) {
    //     mn = gcd(mn, a[i]);
    // }

    // bool eql = false;
    // for (int i = 0 ;i < n; ++i) {
    //     if (a[i] == mn) {
    //         eql = true;
    //         break;
    //     }
    // }
    
    // if (eql) {
    //     int ans = 0;
    //     for (int i = 0; i < n; ++i) if (a[i] != mn) ++ans;
    //     cout << ans << "\n";
    // } else {
    //     for (int i = 0; i < n; ++i) {
    //         a[i] = a[i] / mn;
    //     }
    //     // cout <<"mn ="<< mn << endl;
    //     // print_container(a, "after dividing, a = ");

    //     int ans = 0;
    //     while (true) {
    //         int mini=-1, minj=-1, mn = 1e9;
    //         for (int i = 0; i < n; ++i) {
    //             for (int j = 0; j < i; ++j) {
    //                 int g = gcd(a[i], a[j]);
    //                 if (g < mn) {
    //                     mn = g;
    //                     mini = i;
    //                     minj = j;
    //                 }
    //             }

    //         }

    //         if (a[mini] > a[minj]) {
    //             a[mini] = mn;
    //         } else {
    //             a[minj] = mn;
    //         }

    //         ++ans;
    //         // print_container(a, "a = ");
    //         if (mn == 1) {
    //             break;
    //         }
    //     }
    //     cout << ans + n - 1 << "\n";
    // }

    /*
    actually correct solution:
    so we can do the same thing as above, except we need to change how we determine the smallest
    number of operations needed to get at least one instance of our final value into the array.
    we can use DP, where mem[i] is the minimum number of operations that we need in order to get
    an element of i into our array. we can iterate over i descending, and then for each of those,
    we can iterate over all of our elements a_j and update mem[gcd(i, a_j)], because we'll only
    need one more operation to get from i to gcd(i, a_j). however, this is just a little bit too
    slow, because calculating gcd(i, a_j) will take log(max(i, a_j)). so, we can actually have
    ANOTHER lookup table (read: DP table) where we memoize the results of the gcd of all possible
    pairs of numbers from 1 to max(a), so then since we are going through all pairs (p, q) where
    1 <= p, q <= max(a), each operation will amortized take O(1). this lookup table for gcds between
    two integers can either be computed on the fly or precomputed. our final time complexity will
    basically be O(max(a)^2 + max(a)*n).

    generalizable ideas?
    the construction of the table of memoized results is indexed by the possible values of our
    final value. it's also filled in from larger indices to smaller ones (which in this case is
    relatively intuitive). see, this is related to the difference between indexing the DP table
    either by the number of elements you are using vs. indexing it by the numerical value of a
    variable in the problem that i discussed in CF2114F; in this case, it's the latter.
    also, this is almost like a multilayer DP solution. on the outer layer, we actually have our
    DP problem, but on our inner layer, we know that we want to be able to index that original,
    outer DP table using GCDs and we need to speed up the process of calculating GCDs, so we
    can have a lookup table (our inner layer of DP) that stores the GCDs of pairs of values
    themselves.
    the outer layer of DP (for storing the operations needed to get a gcd of i in the array)
    involves an interesting way of filling in the DP table that has probably shown up before
    and will probably show up again. it's common to have a table like mem[n][m], and then to
    iterate 1<=i<=n and 1<=j<=m and fill in mem[i][j] at each iteration of the innermost loop.
    in this problem, though, we iterate over the final gcd value (let's call it g) and the
    elements in the array (let's call each one ai), and at each iteration we fill in
    mem[gcd(g, ai)]. what this basically comes down to is doing some extra computation to find
    which index of the DP table we want to fill in. also, this is only tangentially related,
    but keep in mind that the only elements of the DP table that will get filled in correspond
    to the indices that are divisors of at least one of the elements of the original array.

    questions to answer:
    if each operation modifies the array in-place, then we would want to apply a series of
    operations in-place to get our final GCD value somewhere in the array; why is it okay
    for the memoized result at a specific state in the DP table to be updated using values
    from the original array and not the array after the updates needed to get to that state?
    */

    int n;
    cin >> n;
    vector<int> a(n);
    int maxa = 0, finalgcd = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        maxa = max(maxa, a[i]);
        finalgcd = gcd(finalgcd, a[i]);
    }

    vector<int> cnt(maxa+1, 0);
    for (int i = 0; i < n; ++i) cnt[a[i]] += 1;
    if (cnt[finalgcd]) {
        cout << n - cnt[finalgcd] << "\n";
        return;
    }

    // cnt[finalgcd] == 0
    vector<int> mem(maxa+1, 1e9); for (int i = 0; i < n; ++i) mem[a[i]] = 0; // 0 ops needed to get a value already there
    for (int i = maxa; i >= finalgcd; --i) {
        for (int j = 0; j < n; ++j) {
            int g = memoized_gcds[max(i, a[j])][min(i, a[j])];
            // cout << "gcd of "<<i<<" and "<<a[j] << " is "<<g<<"\n";
            mem[g] = min(mem[g], mem[i] + 1);
        }
    }
    // for (int row = 0; row <= maxa; ++row) print_container(mem2[row]);
    cout << mem[finalgcd] + n - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i <= 5000; ++i) {
        for (int j = 0; j <= i; ++j) {
            lookup_gcd(i, j, memoized_gcds);
        }
    }

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
