#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    string v;
    cin >> v;
    int vlen = v.length();

    // map char to int for original
    string s;
    cin >> s;
    int slen = s.length();

    // find minLen
    unordered_map<char, bool> visited;
    int visited_count = 0;
    int minLen = 0;
    for (char c : v) {
        visited[c] = false;
    }
    for (char c : s) {
        if (!visited[c]) {
            visited[c] = true;
            visited_count++;
            if (visited_count == v.length()) {
                minLen++;
                visited_count = 0;
                for (char c : v) {
                    visited[c] = false;
                }
            }
        }
    }
    minLen++;
    // cout << "minlen " << minLen << endl;

    // precompute
    vector<map<char, int>> precompute(slen);
    map<char, int> seen;
    for (int j = 0; j < vlen; ++j)
    {
        seen[v[j]] = -1;
    } 
    for (int i = slen - 1; i >= 0; i--) {
        precompute[i] = seen;
        seen[s[i]] = i;
    }

    // for each query
    int numQuery;
    cin >> numQuery;
    for (int x = 0; x < numQuery; ++x)
    {
        string q;
        cin >> q;
        int qlen = q.length();
        if (qlen != minLen)
        {
            cout << "0" << endl;
            continue;
        }

        int index = seen[q[0]];
        if (index == -1) {
            cout << "1" << endl;
            continue;
        }
        bool sad = false;
        for (int i = 1; i < qlen; i++) {
            index = precompute[index][q[i]];
            if (index == -1) {
                cout << "1" << endl;
                sad = true;
                break;
            }
        }
        if (!sad) cout << "0" << endl;
    }
}