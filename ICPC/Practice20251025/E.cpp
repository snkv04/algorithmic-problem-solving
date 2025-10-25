#include <bits/stdc++.h>
using namespace std;


long long gcd(long long a, long long b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

void printv(vector<long long> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void solve() {
    int m, n, p;
    cin >> m >> n >> p;

    if (n == 0 || p == 0) {
        if (n == p) cout << "1/1" << endl;
        else cout << "0/1" << endl;
        return;
    }

    vector<long long> nums;
    vector<long long> dens;
    nums.push_back(1);
    dens.push_back(1);
    for (int i = 1; i <= n; i++) {
        nums.push_back(0);
        dens.push_back(1);
    }

    for (int i = 0; i < p; i++) {
        vector<long long> new_nums;
        vector<long long> new_dens;
        new_nums.push_back(0);
        new_dens.push_back(1);
        for (int k = 0; k < n; k++) {
            long long t = new_nums[k];
            long long q = new_dens[k];
            long long r = nums[k] * (m - i - 2 * (n - k));
            long long s = dens[k] * (m - i);
            //cout << "t = " << t << " q = " << q << " r = " << r << " s = " << s << endl;
            t = t * s + q * r;
            q = q * s;
            long long d = gcd(t, q);
            t /= d;
            q /= d;
            new_nums[k] = t;
            new_dens[k] = q;
            //cout << k << " t = " << t << " q = " << q << endl;

            t = nums[k] * 2 * (n - k);
            q = dens[k] * (m - i);
            d = gcd(t, q);
            t /= d;
            q /= d;
            new_nums.push_back(t);
            new_dens.push_back(q);
            //cout << k << " t = " << t << " q = " << q << endl;
        }
        nums = new_nums;
        dens = new_dens;
        //cout << "after " << i << endl;
        //printv(nums);
        //printv(dens);
    }

    cout << nums[n] << "/" << dens[n] << endl;
}

int main() {
    solve();
    return 0;
}