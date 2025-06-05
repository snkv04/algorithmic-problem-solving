#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void solve() {
    int n;
    cin >> n;
    if (true) {
        vector<int> even = {0}, odd = {0};
        unordered_map<int, int> idx;
        for (int i = 1; i <= n; ++i) {
            int ai;
            cin >> ai;
            idx[ai] = i;
            if (i % 2) {
                odd.push_back(ai);
            } else {
                even.push_back(ai);
            }
        }
        sort(odd.begin(), odd.end());
        sort(even.begin(), even.end());

        vector<int> result = {0};
        for (int i = 1; i <= n; ++i) {
            int lowest;
            if (i % 2) {
                lowest = odd[(i+1)/2];
            } else {
                lowest = even[(i+1)/2];
            }
            result.push_back(lowest);
        }
        // print_container(result, "result = ");
        // print_container(even, "even = ");
        // print_container(odd, "odd = ");

        // bool last2orderedeven = idx[even[even.size()-2]] < idx[odd[odd.size()-2]];
        // bool last2orderedodd = idx[even[even.size()-1]] < idx[odd[odd.size()-1]];
        // // cout << "last2orderedeven = " << last2orderedeven << ", last2orderedodd = " << last2orderedodd << "\n";
        // if (last2orderedeven != last2orderedodd) {
        //     swap(result[n], result[n-2]);
        // }

        for (int i = 1; i <= n; ++i) {
            cout << result[i] << " ";
        }
        cout << "\n";
    } else {
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i += 2) {
            int a, b;
            cin >> a >> b;
            v.push_back(make_pair(a, b));
        }
        sort(v.begin(), v.end());
        for (auto p : v) {
            cout << p.first << " " << p.second << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
