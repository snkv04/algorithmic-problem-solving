#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct dsu {
    vector<int> v;
    void init(int N) {
        for (int i = 0; i < N; i++) {
            v.push_back(-1);
        }
    }
    int root(int i) {
        if (v[i] < 0) return i;
        return v[i] = root(v[i]);
    }
    void merge(int i, int j) {
        i = root(i);
        j = root(j);
        if (i == j) return;
        if (v[i] < v[j]) {
            v[i] += v[j];
            v[j] = i;
        } else {
            v[j] += v[i];
            v[i] = j;
        }
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    dsu d;
    d.init(N);
    for (int i = 0; i < M; i++) {
        int k, l;
        cin >> k >> l;
        d.merge(k, l);
    }
    //for (int i = 0; i < N; i++) {
     ///   cout << d.v[i] << " ";
    //}
    ll count = 0;
    for (int i = 0; i < N; i++) {
        if (d.v[i] < 0) {
            count += d.v[i] * (d.v[i] + 1LL)/2;
        }
    }
    
    cout << fixed << setprecision(12) << ((long double) count) / (N * (N - 1LL) / 2) << endl;
}