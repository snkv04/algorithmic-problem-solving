#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ld abst(ld a) {
    return a < 0 ? -a : a;
}

int main() {
    int N;
    cin >> N;
    vector<int> x(N, 0);
    vector<int> y(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
    }

    ld total_area = 0;
    for (int i = 1; i < N - 1; i++) {
        total_area += abst((ld) x[0]*y[i]+x[i]*y[i+1]+x[i+1]*y[0] - y[0]*x[i]-y[i]*x[i+1]-y[i+1]*x[0]);
    }

    total_area /= 2;

    for (int i = 1; i < N - 1; i++) {
        ld triangle_area = abst((ld) x[0]*y[i]+x[i]*y[i+1]+x[i+1]*y[0] - y[0]*x[i]-y[i]*x[i+1]-y[i+1]*x[0]);
        total_area -= triangle_area;
        if (total_area < 0) {
            ld ratio = abst(total_area) / triangle_area;
            ld ansx = x[i+1] + (x[i] - x[i+1]) * ratio;
            ld ansy = y[i+1] + (y[i] - y[i+1]) * ratio;
            cout << fixed << setprecision(12) << ansx << " " << ansy << endl;
            break;
        }
    }
}