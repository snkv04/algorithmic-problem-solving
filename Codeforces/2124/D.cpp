#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

bool check_palindrome(vector<int> &v) {
    int n = v.size();
    for (int i = 0; i < n/2; ++i) {
        if (v[i] != v[n-1-i]) return false;
    }
    return true;
}

void solve() {
    /*
    basically:
    - observe that what the problem statement is saying is that we can remove
    all of the top n-k+1 elements
    - there may or may not be a lot of elements that are equal to the k'th smallest
    element, but all of the elements that are strictly smaller cannot be removed while
    all of the elements that are strictly greater can be removed without reducing the
    possibility of making the string into a palindrome
        - why are we putting all of the instances of the k'th smallest element into
        its own category? because we can definitely remove at least 1 but there's no
        guarantee we can remove all of them. since we might not be able to remove all of
        them, we have to be strategic in removing some of htem
    - now, just check if the elements that you can't remove form a palindrome. if not,
    then you can't make a palindrome at all
    - if so, then check to see what the minimum number of elements you need to remove to
    make a palindrome is. you can do this by first removing all the elements strictly
    greater than the k'th smallest element, and then, among the remaining elements (those
    that are <= the k'th smallest element), removing the minimum number of threshold elements
    needed to make the overall sequence symmetrical
        - the way i used was to look at the underlying array of elements that cannot be
        removed/changed, and identify the center of that array in the larger array with the
        removable elements. then, move outward in the two directions, identifying the blocks
        that are separated by the elements that cannot be changed. the part after and before
        have the non-changeable elements being symmetric but the changeable elements possibly
        not being symmetric. so, we iterate through each "block" of changeable elements (bounded
        by the elements less than the k'th smallest), and for each we find the minimum number
        of elements needed to be removed so that it's equal on the left and right half (in other
        words, the difference between the number of changeable elements in that block on the
        left half vs on the right half). then, we can sum the required operations from all of
        these blocks up
        4444 3 44 2 1 444 1 4444 2 4444 3 4444
        - another, simpler way is to just use two pointers. we COULD check beforehand that
        the underlying elements form a palindrome. if we do, we just repeatedly push the pointers
        in, moving them both in whenever they're matching (because if they're matching elements,
        then we don't have to remove anything to keep it a palindrome), and incrementing the
        number of elements we have to remove and pushing one pointer in if they're not matching,
        because we'd have to remove that element to make it a palindrome. what happens if we
        don't check beforehand that the underlying array is a palindrome? then, the only difference
        is that among the elements less than the threshold, they're not symmetrical, so the left
        and right pointer might have different elements that are both not equal to the threshold.
        this is easy to deal with, as we can just set a condition to check for it
    - finally, just check if that minimum number of elements required to remove is leq
    the maximum allowable elements to remove

    even simpler:
    - find the k'th smallest element
    - in the same order, remove all the elements greater than it
    - check to make sure that the unchangeable elements form a palindrome
    - find the minimum number of elements to remove to keep the changeable elements
    symmetric about the center of the unchangeable elements
    - check if that minimum number of required operations leaves at least k-1 remaining
    elements

    generalizeable patterns?
    - if you have a palindrome, you can remove elements from it and make another palindrome
    - when aligning two sequences together, check to see if contiguous parts of each sequence
    (in this problem, they are contiguous strings of elements strictly less than the threshold)
    need to be treated as groups or as separate. my in-contest submission was wrong strictly
    because i treated these consecutive groups as together, when each element should have been
    treated as separate. in general, when iterating over sequences and there are consecutive
    segments of alike elements, consider whether they should be treated as together or each element
    in the consecutive segment is separate from each other
    - a common pattern is that when you have to impose some constraint on something (here, we
    are enforcing that the part after the center and before the center are mirrors of each other),
    break it up into pieces that are required to be equal to each other and just iterate through
    those pieces. for example, in this problem, we want to find the minimum number of operations
    needed to make the second half a mirror of the first by removing some elements that are equal
    to some value. to do this, recognize that we can split up the first and second halves into
    segments that are separated by the elements that cannot be changed, and then for the segments
    in between those separators, just find the minimum number of operations to make those corresponding
    segments equal to each other
    - when aligning the first and second parts of a string to make it a palindrome (by removing
    elements), we could do the thing where we align the strings by blocks that must be equal 
    (basically, by bounding those blocks with elements that we can't change), but another, easier
    way is to initialize two pointers to the ends of the string and then move them inward,
    deleting elements when they don't align just like in the algorithm for LCS
        - in general, this would be pretty hard to compute, because knowing which elements to
        remove might require some sort of computation of LCS, which is slow. (the reason for
        this is that we don't know which substring of the original string will end up being
        the palindrome.) however, in this particular case, we know that there are some elements
        which you can't operate on and some elements which you can operate on. by performing
        that simplification, since you DO KNOW which substring of the original string will
        end up being the palindrome (as well as where the center of the palindrome will be),
        you don't need to do LCS and can instead do the two-pointer approach (which, i guess,
        is kind of a variation of LCS, but it's in O(n) instead of O(n^2))
        - specifically, HOW do we move from LCS to an O(n) two-pointer approach? with LCS,
        you are trying to find the maximal overlapping sequence, so you have to check all
        possible prefixes for the first and the second strings like a Cartesian product.
        with this case, you know what the maximal overlapping sequence will be (except for
        the threshold values, but you know that matching threshold values on teh left and
        right pointer need not be removed as it stays a palindrome if you don't remove them
        plus you don't waste operations), so you already know which pointer to push forward
        instead of trying all possible combinations of pushing both pointers forward. this
        transforms it from O(n^2) to O(n).
    - in some cases, if we want to optimize something while keeping it under a constraint,
    we could use that constraint in the process of optimizing it (which is often the case
    in dynamic programming). in other cases, we can just simply optimize the value globally
    as much as possible, without using that constraint as input, and then just check at the
    end if the optimized value meets the constraint. it seems to often be the case that if
    we are constraining the number of operations to be under some value, we just globally
    try to minimize the number of operations, and then perform a simple check to see if it's
    under that value, such as what was done here in this problem
    */

    int n, k;
    cin >> n >> k;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> b = a;
    sort(b.begin(), b.end());

    if (k <= 2) {
        cout << "YES\n";
        return;
    }

    int threshold = b[k-1];
    vector<int> c, d; // d has at least 1 threshold element, which c doesn't have
    for (int ai : a) {
        if (ai < threshold) c.push_back(ai);
        if (ai <= threshold) d.push_back(ai);
    }
    // cout << "threshold = " << threshold << "\n";
    // print_container(b, "b = ");
    // print_container(c, "c = ");
    // print_container(d, "d = ");

    if (check_palindrome(c)) {
        // if (d.size() == c.size()) {
        //     cout << "YES\n";
        //     return;
        // }
        if (c.size() == 0) {
            // cout << "c was empty\n";
            cout << "YES\n";
            return;
        }

        int canremove = (d.size() - k) + 1;
        // vector<int> compressed;
        // for (int di : d) {
        //     if (di == threshold) compressed.push_back(di);
        //     else {

        //     }
        // }
        int firstright = -1, lastleft = -1; // indices in d
        if (c.size() % 2) {
            int numless = 0;
            for (int i = 0; i < d.size(); ++i) {
                if (d[i] < threshold) {
                    ++numless;

                    if (numless == (c.size()+1)/2) {
                        lastleft = i-1;
                        firstright = i+1;
                        break;
                    }
                }
            }
        } else {
            int numless = 0;
            for (int i = 0; i < d.size(); ++i) {
                if (d[i] < threshold) {
                    ++numless;

                    if (numless == c.size()/2) {
                        lastleft = i;
                    }
                    if (numless == c.size()/2+1) {
                        firstright = i;
                        break;
                    }
                }
            }
        }
        // cout << "lastleft = "<<lastleft<<", firstright = "<<firstright<<"\n";

        unordered_map<int, int> leftfreqs, rightfreqs;
        int breaks = 0;
        for (int i = firstright; i < d.size(); ++i) {
            if (d[i] == threshold) {
                rightfreqs[breaks] += 1;
            } else {
                // if (i == firstright || d[i-1] == threshold) {
                    ++breaks;
                // }
            }
        }
        breaks = 0;
        for (int i = lastleft; i >= 0; --i) {
            if (d[i] == threshold) {
                leftfreqs[breaks] += 1;
            } else {
                // if (i == lastleft || d[i+1] == threshold) {
                    ++breaks;
                // }
            }
        }
        // print_container(leftfreqs, "lf=");
        // print_container(rightfreqs, "rf=");

        // compare left and right
        int mustremove = 0;
        unordered_set<int> keys;
        for (const auto &p : leftfreqs) keys.insert(p.first);
        for (const auto &p : rightfreqs) keys.insert(p.first);
        for (int k : keys) {
            int l = (leftfreqs.find(k) == leftfreqs.end()) ? 0 : leftfreqs[k];
            int r = (rightfreqs.find(k) == rightfreqs.end()) ? 0 : rightfreqs[k];
            // cout << "adding " << max(l-r,r-l) << " to mustremove\n";
            mustremove += max(l-r, r-l);
        }
        // cout << "mustremove = " << mustremove << ", canremove = " << canremove << "\n";
        cout << ((mustremove <= canremove) ? "YES" : "NO") << "\n";
    } else {
        // cout << "c wasn't a palindrome\n";
        cout << "NO\n";
    }
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
