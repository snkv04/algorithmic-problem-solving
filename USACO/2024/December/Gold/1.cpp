#include <bits/stdc++.h>
using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream &os, const set<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

vector<int> makenext(const set<int> &indices, int n) {
    vector<int> next(n, n);
    auto it = indices.begin();
    for (int i = 0; i < n && it != indices.end(); ++i) {
        if (i <= *it) {
            next[i] = *it;
            if (i == *it) ++it;
        }
    }
    return next;
}

int main() {
    /*
    - for subtask 3, if all the labels have 10 cows each, then the complexity is O(N/10 * 10^2 * log(N)).
    however, if they all have 1 cow each, then the complexity is O(N/1 * 1^2 * log(N)). doesn't this mean
    that, since the labels can have <= 10 cows, the complexity should be O(N * 10^2 * log(N))? no, because
    if we reduce the maxfreq of a given label, then the second term diminishes much quicker than the first
    term grows. in the "all labels have max frequency" case, then the complexity is definitively
    O(N/10 * 10^2 * log(N)), and if some labels have lower frequency, then since the stated complexity
    represents the sum of complexities over all labels, we are able to look at each label individually, and
    we can see that for those labels with lower frequency, the second term diminished far quicker than the
    first term grows. it's weird, sure, because the sum representing the complexity is such that the different
    terms have different complexities, but they are upper-bounded by O(N/F * F^2 * log(N)) = O(N * F * log(N)),
    where F is the max frequency of a label.
    - the core idea: if the number of labels is low but the frequency of each label can be high, we have
    an efficient algorithm taking advantage of the fact that there are few labels. if the number of labels can
    be high but the frequency of each label is low, then we have another efficient algorithm taking advantage
    of the fact that each label only shows up a few times. the key observation is that we set an upper bound
    for the frequency of labels falling in the second group, then the number of labels might be N (which doesn't
    logically help us much), but if we set a lower bound F for the frequency of the labels that fall into the first
    group, then the number of labels in that group is then upper bounded by N/F. in other words, the WAY IN WHICH
    we keep the number of labels low is by WILLINGLY ensuring that the frequency of each label is high. then, we
    fall into our two separate cases. to set our frequency bound, we see that one of the complexities increases
    linearly with x and one of them decreases inversely with x. to upper-bound both of them, we need them to be
    equal, so we literally just solve for F^2 = N --> F = sqrt(N).

    generalizable ideas for the future:
    - if two methods have inversely proportional complexities (which means that one scales up with one variable
    and another scales down with one variable), and both of those methods might be used, then in order to minimize
    the max of those two, we want them to be equal. in simpler terms: to minimize the max of two functions, where
    one decreases and the other increases, find the point where they're equal.
    - in big-O notation, if a value f can be <= F but there is a specific value (such as F) that maximizes the
    time complexity, then we assume that f takes on that maximum value. similarly, if O(g(f_1, f_2, ..., f_k))
    = O(h(f_1) + h(f_2) + ... + h(f_k)), and there is a value for each f_i that maximizes h(f_i), then we assume
    that each f_i is that value.
        - in this problem, each label's frequency f can be <= F, but note that if f < F, then we have that the
        time complexity for that label decreases quite quickly due to the square term. if count(f_i) is the number
        of times that there's a label with frequency f_i, then the time complexity of the small-frequency labels
        collectively is
        O(f_1^2 * log(N) + f_2^2 * log(N) + ... + f_k^2 * log(N)) =
        O(count(1) * 1^2 * log(N) + count(2) * 2^2 * log(N) + ... + count(F) * F^2 * log(N)). however, observe
        that even though the total number of labels might exceed N/F and reach N due to lots of labels with low
        frequency (i.e., since f << F, then count(f) approaches N), the overall time complexity actually decreases
        if there are more labels with really low f_i, because count(f_i) might increase linearly but f_i^2 decreases
        by the square of f_i. in other words, the reason that this is important is that to get the upper bound of
        the time complexity, the worst case actually does happen when f_i == F for all f_i, so then the complexity
        is O(count(F) * F^2 * log(N)) = O(N/F * F^2 * log(N)) = O(N*F*logN). the unintuitive part is that it seems
        like if labels have lower frequency then the time complexity gets worse because the number of those labels
        increases (which is true), but the time complexity actually overall gets better because the cost decreases
        more rapidly due to the squared term drastically dropping if the frequency drops, so cases where the frequency
        for lots of labels is lower isn't actually the worst case. as a result, the worst-case is actually letting
        all f_i == F, which then allows us to write the complexity formula in the way that it's written.
    - the way in which we keep one thing low (so then it can be brute-forced) can be to keep some other thing high.
    - the labels can be separately solved based on their size.
    - there are several ways of counting the same thing. if the time limit is being exceeded, there are probably
    multiple ways of speeding up the same thing, and if one process is used multiple times, then it might be the case that
    it can be sped up in one way in one place that it's used and in a different way in another place that it's used.
    if the contexts of those two ways differ (such as in this problem, where we can make the `next` array without
    much cost if freq >= F, but not if freq < F), then that could help inform how we want to speed up the process.
    */

    int n;
    cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    map<int, set<int>> indices;
    for (int i = 0; i < n; ++i) {
        indices[a[i]].insert(i);
    }
    // for (auto e : indices) {
    //     cout << "indices[" << e.first << "] = " << e.second << endl;
    // }

    int f = sqrt(n);
    vector<int> ans(n+1, 0), pref(n+1, 0);
    for (auto e : indices) {
        const set<int> &i = e.second;
        // cout << "processing label " << e.first << endl;
        if (i.size() >= f) {
            vector<int> next = makenext(i, n);
            for (int x = 1; x <= n; ++x) {
                // counts groups by jumping forward by x and finding next valid index through precomputation
                int cnt = 1, curr = *i.begin();
                while (curr+x+1 < n && next[curr+x+1] != n) {
                    ++cnt;
                    curr = next[curr+x+1];
                }
                ans[x] += cnt;
                // cout << "num groups when x = " << x << " is " << cnt << endl;
            }
        } else {
            int cnt = i.size();
            vector<int> vec(i.begin(), i.end());
            sort(vec.begin(), vec.end());
            pref[0] += cnt+1;
            for (int numgroups = cnt; numgroups >= 1; --numgroups) { // loop order doesn't matter
                int l = 1, r = n, x = -1; // x = smallest value of x that results in <= numgroups groups
                while (l <= r) {
                    int m = l + (r - l) / 2;

                    // counts groups by jumping forward by x and finding next valid index dynamically
                    // int g = 1, curr = *i.begin();
                    // while (i.upper_bound(curr + m) != i.end()) {
                    //     ++g;
                    //     curr = *i.upper_bound(curr+m);
                    // }

                    // counts groups by looping through valid indices linearly, and checking
                    // if we performed a jump by more than x
                    int g = 1, left = 0, right = 0;
                    while (right < vec.size()) {
                        if (vec[right] - vec[left] > m) {
                            ++g;
                            left = right;
                        }
                        ++right;
                    }

                    if (g <= numgroups) {
                        x = m;
                        r = m - 1;
                    } else {
                        l = m + 1;
                    }
                }

                if (x == -1) pref[0] -= 1;
                else pref[x] -= 1;
            }
        }
    }

    for (int i = 1; i <= n; ++i) pref[i] += pref[i-1];
    for (int i = 1; i <= n; ++i) cout << ans[i] + pref[i] << '\n';
}
