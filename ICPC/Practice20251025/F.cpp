#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld pi = acos(-1.0);

struct Circle {
    ld x, y, r, s;
};

struct DSU {
    int n;
    vector<int> parent;

    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        else {
            return parent[x] = find(parent[x]);
        }
    }

    void unite(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            parent[d] = c;
        }
    }
};

void solve() {
    int n;
    cin >> n;
    
    vector<Circle> circles;
    for (int i = 0; i < n; ++i) {
        ld x, y, r, s;
        cin >> x >> y >> r >> s;
        circles.push_back(Circle{x, y, r, s});
    }

    while (circles.size() > 1) {
        n = circles.size();
        ld mintime = 1e18;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                Circle c1 = circles[i], c2 = circles[j];
                
                ld dist = sqrt(
                    (c2.x - c1.x) * (c2.x - c1.x)
                    + (c2.y - c1.y) * (c2.y - c1.y)
                );
                ld time;
                if (c1.r + c2.r >= dist) {
                    time = 0;
                } else {
                    ld rem = dist - c1.r - c2.r;
                    time = rem / (c1.s + c2.s);
                }
                
                mintime = min(mintime, time);
            }
        }

        for (int i = 0; i < n; ++i) {
            circles[i].r += mintime * circles[i].s;
        }

        DSU dsu(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                Circle c1 = circles[i], c2 = circles[j];
                
                ld dist = sqrt(
                    (c2.x - c1.x) * (c2.x - c1.x)
                    + (c2.y - c1.y) * (c2.y - c1.y)
                );
                if (c2.r + c1.r >= dist - 1e-6) {
                    dsu.unite(i, j);
                }
            }
        }

        map<int, vector<int>> components;
        for (int i = 0; i < n; ++i) components[dsu.find(i)].push_back(i);

        vector<Circle> newcircles;
        for (const pair<int, vector<int>> entry : components) {
            vector<int> circleindices = entry.second;

            ld x = 0, y = 0;
            for (int i : circleindices) {
                x += circles[i].x;
                y += circles[i].y;
            }
            x = x / (ld) circleindices.size();
            y = y / (ld) circleindices.size();

            ld areasum = 0;
            for (int i : circleindices) {
                areasum += pi * circles[i].r * circles[i].r;
            }
            ld newr = sqrt(areasum / pi);

            ld news = 0;
            for (int i : circleindices) news = max(news, circles[i].s);

            newcircles.push_back(Circle{x, y, newr, news});
        }

        circles = std::move(newcircles);
    }

    Circle c = circles[0];
    cout << fixed << setprecision(12) << c.x << " " << c.y << endl << c.r << endl;
}

int main() {
    solve();
    return 0;
}
