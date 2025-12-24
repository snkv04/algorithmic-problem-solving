#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("highcard.in");
    ofstream cout("highcard.out");

    int n;
    cin >> n;
    vector<int> strategy;
    set<int> elsie, bessie;
    for (int i = 0; i < n; ++i) {
        int card;
        cin >> card;
        strategy.push_back(card);
        elsie.insert(card);
    }

    for (int i = 1; i <= 2*n; ++i) {
        if (elsie.find(i) == elsie.end()) {
            bessie.insert(i);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int card = strategy[i];
        auto it = bessie.upper_bound(card);
        if (it != bessie.end()) {
            ans += 1;
            bessie.erase(it);
        }
    }
    cout << ans << endl;
}
