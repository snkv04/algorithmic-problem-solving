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

bool query(string s) {
    cout << "? " << s << endl;
    int result;
    cin >> result;
    return result;
}

void print(string s) {
    cout << "! " << s << endl;
}

void solve() {
    /*
    key idea: you can build the string from left to right, but you don't know what position you're
    starting from, so you might hit the end at the right side. however, you'll only hit the end once,
    and after that, you just build the string going in the leftward direction
    */

    int n;
    cin >> n;
    if (n == 1) {
        cout << "? 0" << endl;
        int res; cin >> res;
        if (res) {
            cout << "! 0" << endl;
        } else {
            cout << "! 1" << endl;
        }
    } else {
        string curr = "0";
        bool goingright = true;
        for (int i = 2; i <= n; ++i) {
            if (goingright) {
                curr += '0';
                if (query(curr)) {
                    continue;
                }
    
                curr = curr.substr(0, curr.size() - 1);
                curr += '1';
                if (!query(curr)) {
                    // have to flip directions
                    goingright = false;
                    curr = curr.substr(0, curr.size() - 1);
                    curr = '1' + curr;
                    if (!query(curr)) {
                        if (curr.size() == 2) {
                            curr = "11"; // in fact, the whole string will just be 1s, but that will be dealt with later anyway
                        } else {
                            curr = '0' + curr.substr(1, curr.size() - 1);
                        }
                    }
                }    
            } else {
                curr = '0' + curr;
                if (!query(curr)) {
                    curr = '1' + curr.substr(1, curr.size() - 1);
                }
            }
        }
        print(curr);
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
