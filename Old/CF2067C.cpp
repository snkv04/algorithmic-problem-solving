#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

ll getdigit(ll n, ll idx) {
    while (idx) {
        n /= 10;
        --idx;
    }
    return n % 10;
}

ll pow(ll b, ll p) {
    if (p == 0) return 1;
    ll result = pow(b, p/2);
    result *= result;
    if (p % 2) {
        return result * b;
    } else {
        return result;
    }
}

void solve() {
    /*
    first off, it's clear that the answer is <= 9. one way to deal with this problem is to
    recognize that the final digit will be one of a finite set of digits (either one of those
    present in n or the leading zero after it), so we can iterate over each of these digits
    and find the fastest way to bring that digit to a 7, and then take the minimum of these
    answers across all possible digits. clearly each of the numbers that are just repeated
    9s are simply powers of 10 minus 1, so one of the key observations here is that adding
    any of them (let's call it 10^p - 1) to a number n will increment the digit at the 10^p
    place and decrement the digit at the 1s place, possibly cascading the decrements to the
    left if the digit goes from 0 to 9. in the extreme case, such as 1000+999, the digit at
    the 10^p place will not actually change at all. however, we can show that, if we want
    to change the digit at the 10^p place, no "9-repeating" number will change it faster than
    the one equal to 10^p-1: all digits to the left will have absolutely no impact on that
    digit, and for any smaller 9-repeating number (such as 10^(p-1)-1) that would change the
    digit at place 10^p of n, the number 10^p-1 would also change the same digit by the same
    amount since it adds the same amount (and then more, but not so much that it reverts the
    change to the digit). for example, if we're trying to change the 10^3 place of 2901,
    then 99 would work but so would 999, so might as well just always use 999. for this reason,
    we can just iterate over the digits, moving them to 7 as fast as possible through the
    operation that moves that digit the fastest.
    (never mind, something about the reasoning above is incorrect; ignore it.)
    another way to deal with this problem that also elegantly deals with the cases of 10^p-1
    not always changing the 10^p digit is to iterate over the number of operations we're going
    to do, fixing it in place for each iteration. since we know we're going to use exactly k
    operations, regardless of whether we use the same 9-repeating number for the operations or
    different ones each time, we're always going to be adding k powers of 10 and subtracting
    1 k times. so, we can look at n-k, and then only focus on moving digits themselves through
    adding powers of 10. in other words, the key observation here is that we separate out the
    10^p addition and the 1 subtraction of each operation, applying the subtraction part first
    to make the changing digits part straightforward. then, it becomes clear that each digit
    can be moved most efficiently (with similar logic to before, but even more simple since
    there are no special cases after having already done the subtraction) by just doing the
    same operation over and over. then, the algorithm then becomes to iterate over the number
    of operations being done, subtract the number of operations from n to account for the "-1"
    part of the expression 10^p-1, and then to iterate over each digit (suppose we say that
    it's in the 10^p place) and see how many times we have to add 10^p to make that digit equal
    to 7, accepting it if that number of times is less than or equal to the operations we plan
    to apply.
    put simply, we separate out the +10^p part and the -1 part, and once we've applied the -1
    part, then we can straightforwardly apply the +10^p parts, and they don't all have to be
    on the same digit. we find how many operations we have available to apply by iterating
    over that value and setting it as fixed per each iteration of the loop.
    */

    ll n;
    cin >> n;
    ll ans = 1e9;
    for (int ops = 0; ops <= 9 && ans == 1e9; ++ops) {
        ll n2 = n - ops;
        while (true) {
            int digit = (n2 % 10);
            if ((17 - digit) % 10 <= ops) {
                ans = ops;
                break;
            }

            if (n2 == 0) break;
            n2 /= 10;
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
