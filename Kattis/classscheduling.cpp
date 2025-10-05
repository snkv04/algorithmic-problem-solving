#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

int ans;

void recurse(vector<vector<pair<int, int>>> &sections, vector<pair<int, int>> &schedule) {
    if (sections.empty()) {
        ans = min(ans, schedule.back().second - schedule.front().first);
        return;
    }

    for (int course = 0; course < sections.size(); ++course) {
        vector<pair<int, int>> possible_sections = sections[course];
        sections.erase(sections.begin() + course, sections.begin() + course + 1);
        for (int sec = possible_sections.size() - 1; sec >= 0; --sec) {
            if (schedule.empty() || possible_sections[sec].first >= schedule.back().second + 15) {
                schedule.push_back(possible_sections[sec]);
                recurse(sections, schedule);
                schedule.pop_back();
            }
        }
        sections.insert(sections.begin() + course, possible_sections);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> sections(n);
    for (int i = 0; i < n; ++i) {
        string name; int num_sections;
        cin >> name >> num_sections;
        while (num_sections--) {
            string start, end;
            cin >> start >> end;

            stringstream ss(start);
            string s;
            getline(ss, s, ':'); int starth = stoi(s);
            getline(ss, s); int startm = stoi(s);
            ss.clear();
            ss.str(end);
            getline(ss, s, ':'); int endh = stoi(s);
            getline(ss, s); int endm = stoi(s);

            sections[i].push_back({starth * 60 + startm, endh * 60 + endm});
        }
        sort(sections[i].begin(), sections[i].end());
    }

    ans = 1e9;
    vector<pair<int, int>> schedule;
    recurse(sections, schedule);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
