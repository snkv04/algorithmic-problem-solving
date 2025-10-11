#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct ByRatio {
    bool operator()(const array<ll, 3> &a, const array<ll, 3> &b) const {
        ll first = a[2] * b[0];
        ll second = b[2] * a[0];
        if (first != second) return first < second;
        else return a[1] < b[1];
    }
};

struct ByPos {
    bool operator()(const array<ll, 3> &a, const array<ll, 3> &b) const {
        return a[1] < b[1];
    }
};

template <typename C>
void print_set(set<array<ll, 3>, C> s, string prefix) {
    cout << prefix << endl;
    for (auto elem : s) {
        for (int j = 0; j < 3; ++j) {
            cout << elem[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ll imbalance = 0;
    int n = 0; 
    cin >> n;
    set<array<ll, 3>, ByPos> by_pos;
    set<array<ll, 3>, ByRatio> by_ratio;
    vector<ll> ps;
    vector<ll> ws;
    for (int i = 0; i < n; i++) {
        ll p,w;
        cin >> p >> w;
        ps.push_back(p);
        ws.push_back(w);
        imbalance += p * w;
    }

    for (int i = 0; i < n; i++) {
        if (imbalance < 0) {
            array<ll, 3> add = {1, -ps[i], ws[i]};
            by_pos.insert(add);
            by_ratio.insert(add);
        } else {
            array<ll, 3> add = {1, ps[i], ws[i]};
            by_pos.insert(add);
            by_ratio.insert(add);
        }
    }
    if (imbalance < 0) {
        imbalance *= -1;
    }
    

    ll dist = 0;
    while (imbalance != 0) {
        //cout << imbalance << endl;
        //print_set(by_pos, "by_pos");
        //print_set(by_ratio, "by_ratio");
        //cout << endl;

        array<ll, 3> back = *by_ratio.rbegin();
        ll n1 = back[0];
        ll p1 = back[1];
        ll w1 = back[2];
        auto it = by_pos.lower_bound(back);
        if (it == by_pos.begin()) {
            cout << fixed << setprecision(12) << dist + (long double) n1 * imbalance / (long double) w1 << endl;
            return 0;
        } else {
            --it;
            array<ll, 3> back2 = *it;
            ll n2 = back2[0];
            ll p2 = back2[1];
            ll w2 = back2[2];
            if (imbalance <= w1*(p1 - p2)) {
                cout << fixed << setprecision(12) << dist + (long double) n1 * imbalance / (long double) w1 << endl;
                return 0;
            } else {
                dist += n1*(p1 - p2);
                
                by_pos.erase(back);
                by_pos.erase(back2);
                by_ratio.erase(back);
                by_ratio.erase(back2);
                array<ll,3> next = {n1 + n2, p2, w1 + w2};
                by_pos.insert(next);
                by_ratio.insert(next);

                imbalance -= w1 * (p1 - p2);
            }
        } 
    }
    cout << dist << endl;

    return 0;
}