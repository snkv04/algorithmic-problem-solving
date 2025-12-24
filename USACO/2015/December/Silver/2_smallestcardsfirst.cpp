#include <bits/stdc++.h>
using namespace std;

int main() {
    /*
    - if there exists a strategy where you win some number of cards, then there exists a strategy where you
    win the same number of cards but you only beat the smallest cards. more generally, if you want to construct
    a solution where some assumption or simplification is used, we can check if we can ALWAYS apply that
    simplification by checking if any constructed solution has a congruent solution using that simplification
    */

    ifstream cin("highcard.in");
    ofstream cout("highcard.out");

    int n;
    cin >> n;
    set<int> elsie, bessie;
    for (int i = 0; i < n; ++i) {
        int card;
        cin >> card;
        elsie.insert(card);
    }

    for (int i = 1; i <= 2*n; ++i) {
        if (elsie.find(i) == elsie.end()) {
            bessie.insert(i);
        }
    }

    int ans = 0;
    for (int card : elsie) {
        auto it = bessie.upper_bound(card);
        if (it != bessie.end()) {
            ans += 1;
            bessie.erase(it);
        }
    }
    cout << ans << endl;
}
