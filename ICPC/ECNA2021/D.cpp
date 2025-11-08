#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// const ld dtheta = 7e-7;

ld inte(ld r, ld x1, ld y1, ld x2, ld y2, ll numpoints) {
    // arctan(y2/x2) >= arctan(y1/x1)
    ld thetai = atan2(y1, x1), thetaf = atan2(y2, x2);
    if (thetaf - thetai <= 1e-6) return 0.0;

    ld dtheta = (thetaf - thetai) / numpoints;
    if (x1 == x2) {
        ld k = r * r * r * r / (2 * x1 * x1);  // if x1 is 0 while x1 == x2, then thetaf == thetai so we already caught that
        ld definite = 0;
        auto f = [](ld x) {
            return cos(x) * cos(x);
        };
        for (ld i = thetai; i < thetaf; i += dtheta) {
            ld nexti = i + dtheta;
            definite += (f(nexti) + f(i)) / 2.0 * dtheta;
        }
        return k * definite;
    } else {
        ld m = (y2 - y1) / (x2 - x1);
        ld k = r * r * r * r / (2 * (y1 - m * x1) * (y1 - m * x1));
        auto f = [&m](ld theta) {
            return (sin(theta) - m * cos(theta)) * (sin(theta) - m * cos(theta));
        };
        ld definite = 0;
        for (ld i = thetai; i < thetaf; i += dtheta) {
            ld nexti = i + dtheta;
            definite += (f(nexti) + f(i)) / 2.0 * dtheta;
        }
        return k * definite;
    }

    // ld trianglearea = (x1 * y2 - y1 * x2) / 2.0;
    // if (trianglearea < 0) trianglearea *= -1.0;
    // ld sectorarea = (1.0 / 2.0) * r * r * (thetaf - thetai);
    // ld ratio = sectorarea / trianglearea;
    // return ratio * sectorarea;
}

void solve() {
    ll x0, y0, r;
    cin >> x0 >> y0 >> r;
    int n;
    cin >> n;

    ld thetamax = -1e9, thetamin = 1e9;
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        x[i] -= x0;
        y[i] -= y0;
        ld angle = atan2((ld)y[i], (ld)x[i]);
        thetamax = max(thetamax, angle);
        thetamin = min(thetamin, angle);
    }
    // cout << thetamax << " " << thetamin << "\n";
    
    // guaranteed convex polygon, so range of angles across polygon is at max just pi;
    // so, if it crosses between -pi and pi, then flip it
    if (thetamax - thetamin > acos(-1.0)) {
        for (int i = 0; i < n; ++i) {
            x[i] *= -1;
            y[i] *= -1;
        }
        ld oldmin = thetamin, oldmax = thetamax;
        thetamax = oldmin + acos(-1.0);
        thetamin = oldmax - acos(-1.0);
    }

    // because convex, can break down into outside and inside edges from a specified point
    vector<bool> outside(n, false);
    for (int i = 0; i < n; ++i) {
        ld thisangle = atan2((ld) y[i], (ld) x[i]);
        ld nextangle = atan2((ld) y[(i+1)%n], (ld) x[(i+1)%n]);
        if (nextangle > thisangle) {
            outside[i] = true;
        }
    }
    // for (int i = 0; i < n; ++i) {
    //     cout << outside[i] << " ";
    // }
    // cout << endl;

    ld ans = 1e9;
    ll numpoints = 2;
    while (true) {
        ld nextans = 0;
        for (int i = 0; i < n; ++i) {
            ld xi = x[i], yi = y[i], xf = x[(i+1)%n], yf = y[(i+1)%n];
            if (!outside[i]) {
                swap(xi, xf);
                swap(yi, yf);
            }

            ld area = inte(r, xi, yi, xf, yf, numpoints);
            ld thetai = atan2(yi, xi), thetaf = atan2(yf, xf);
            // cout << "for (x1,y1) = (" << xi << ", " << yi << "), (x2, y2) = (" << xf << ", " << yf << "):\n";
            // cout << "theta_i is " << thetai << ", theta_f is " << thetaf << ", area = " << area << "\n";
            if (!outside[i]) {
                nextans += area;
            } else {
                nextans -= area;
            }
        }

        if (abs(nextans - ans) < 1e-6) {
            break;
        } else {
            ans = nextans;
            numpoints *= 2;
        }
    }
    cout << fixed << setprecision(12) << ans << "\n";
}

int main() {
    solve();
    return 0;
}
