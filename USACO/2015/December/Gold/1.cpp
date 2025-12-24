#include <bits/stdc++.h>
using namespace std;

auto flr(const set<int> &s, int num) {
    auto it = s.lower_bound(num);
    if (it == s.begin()) {
        return s.end();
    } else {
        --it;
        return it;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const set<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

int main() {
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
    // cout << "first = " << elsiefirst << ", second = " << elsiesecond << endl;

    int ans = 0;
    set<int> available, used;
    for (int i = 1; i <= 2*n; ++i)
        if (elsiefirst.find(i)==elsiefirst.end() && elsiesecond.find(i)==elsiesecond.end())
            available.insert(i);
    map<int, int> using_from_first;
    for (int card : elsiefirst) {
        auto it = available.upper_bound(card);
        if (it != available.end()) {
            ++ans;
            // cout << "using " << *it << " to beat " << card << endl;
            used.insert(*it);
            using_from_first[*it] = card;
            available.erase(it);
            // cout << "now, available = " << available << " and used = " << used << endl;
        }
    }
    // cout << "====\n";
    for (int card : elsiesecond) {
        if (flr(available, card) != available.end()) {
            int floor = *flr(available, card);
            ++ans;
            available.erase(floor);
            // cout << "using " << floor << " to beat " << card << endl;
            // cout << "now, available = " << available << " and used = " << used << endl;
        } else if (flr(used, card) != used.end()) {
            auto it = flr(used, card);
            if (available.size() && *available.rbegin() > using_from_first[*it]) {
                ++ans;
                // cout << "went from using " << *it << " to beat " << using_from_first[*it] << " to now instead using " << *available.rbegin() << endl;
                // cout << "and now, " << *it << " is being used to beat " << card << endl;
                available.erase(*available.rbegin());
                used.erase(*it);
                // cout << "now, available = " << available << " and used = " << used << endl;
            }
        }
    }
    // cout << "====\n";
    cout << ans << endl;
}
