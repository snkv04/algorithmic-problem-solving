#include <bits/stdc++.h>
using namespace std;

set<int> flip(set<int> &s) {
    set<int> result;
    for (int num : s) result.insert(-num);
    return result;
}

int run(const set<int> &elsie, set<int> &ours) {
    int ans = 0;
    for (int card : elsie) {
        if (ours.upper_bound(card) != ours.end()) {
            ++ans;
            ours.erase(ours.upper_bound(card));
        }
    }
    return ans;
}

int main() {
    /*
    - since we generally want to have high cards for the first part and low cards for the second part,
    we could simply take the cards we have and allocate the highest N/2 cards to our strategy for the
    first part and the lowest N/2 cards to our strategy for the second part. the core logic is this:
    doing such a split cannot make our outcome worse but can make it better. so, we do the split, and
    then just run the same greedy algorithm from the silver problem on each half
    */

    ifstream cin("cardgame.in");
    ofstream cout("cardgame.out");

    int n;
    cin >> n;
    set<int> elsiefirst, elsiesecond;
    for (int i = 0; i < n; ++i) {
        int card;
        cin >> card;
        if (i < n/2) {
            elsiefirst.insert(card);
        } else {
            elsiesecond.insert(card);
        }
    }

    vector<int> ours;
    for (int i = 1; i <= 2*n; ++i)
        if (elsiefirst.find(i) == elsiefirst.end() && elsiesecond.find(i) == elsiesecond.end())
            ours.push_back(i);
    set<int> oursfirst, ourssecond;
    for (int i = 0; i < n; ++i) {
        if (i < n/2) {
            ourssecond.insert(ours[i]);
        } else {
            oursfirst.insert(ours[i]);
        }
    }
    elsiesecond = flip(elsiesecond);
    ourssecond = flip(ourssecond);
    cout << run(elsiefirst, oursfirst) + run(elsiesecond, ourssecond) << endl;
}
