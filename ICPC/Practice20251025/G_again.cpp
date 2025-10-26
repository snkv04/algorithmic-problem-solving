#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll op(ll a, ll b, char op) {
    if (op == '+') {
        return a + b;
    } else {
        return a * b;
    }
}

void solve() {
    vector<ll> nums(3);
    char op_letter;
    string garbage;
    cin >> nums[0] >> op_letter >> nums[1] >> garbage >> nums[2];

    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            string si = to_string(nums[i]), sj = to_string(nums[j]);
            for (int idxi = 1; idxi < si.size(); ++idxi) {
                for (int idxj = 1; idxj < sj.size(); ++idxj) {
                    vector<ll> copy = nums;
                    string newi = sj.substr(0, idxj) + si.substr(idxi, si.size() - idxi);
                    string newj = si.substr(0, idxi) + sj.substr(idxj, sj.size() - idxj);
                    copy[i] = stoll(newi);
                    copy[j] = stoll(newj);
                    if (op(copy[0], copy[1], op_letter) == copy[2]) {
                        cout << copy[0] << " " << op_letter << " " << copy[1] << " = " << copy[2] << endl;
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    solve();

    return 0;
}
