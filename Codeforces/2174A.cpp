#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Multiset {
    void add(T object) {
        counts[object] += 1;
    }

    void remove(T object) {
        if (counts.find(object) == counts.end()) {
            throw std::logic_error("Object not found in multiset");
        }

        counts[object] -= 1;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    void add(T object, long long delta) {
        assert(delta >= 0);
        counts[object] += delta;
    }

    void remove(T object, long long delta) {
        assert(delta >= 0);
        if (counts.find(object) == counts.end() || counts[object] < delta) {
            throw std::logic_error("Not enough instances of object in multiset");
        }

        counts[object] -= delta;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    long long count(T object) {
        if (counts.find(object) == counts.end()) {
            return 0;
        } else {
            return counts[object];
        }
    }
    
    bool empty() {
        return counts.empty();
    }

    std::unordered_map<T, long long> counts;
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s, t;
        cin >> s >> t;
        Multiset<char> sfreqs, tfreqs;
        for (char c : s) sfreqs.add(c);
        for (char c : t) tfreqs.add(c);

        bool works = true;
        for (auto p : sfreqs.counts) {
            if (tfreqs.count(p.first) < p.second) {
                works = false;
                break;
            }
        }
        if (!works) {
            cout << "Impossible\n";
            continue;
        }

        stringstream remaining;
        for (auto p : tfreqs.counts) {
            for (int i = sfreqs.count(p.first) + 1; i <= p.second; ++i) {
                remaining << p.first;
            }
        }
        string sorted = remaining.str();
        sort(sorted.begin(), sorted.end());

        int i = 0, j = 0;
        stringstream result;
        while (i < s.size() || j < sorted.size()) {
            if (i == s.size()) {
                result << sorted[j++];
            } else if (j == sorted.size()) {
                result << s[i++];
            } else {
                if (sorted[j] < s[i]) {
                    result << sorted[j++];
                } else {
                    result << s[i++];
                }
            }
        }
        cout << result.str() << '\n';
    }

    return 0;
}
