#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    int N;
    cin >> N;
    vector<int> v(N);
    vector<int> u(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> v[i];
    }
    for (int i = 0; i < N; ++i)
    {
        cin >> u[i];
    }
    
    unordered_map<int, int> s;
    unordered_map<int, int> t;
    string output = "";
    for (int i = 0; i < N - 1; i++) {
        output += to_string(u[i]) + " ";
        if (t.find(v[i]) != t.end()) {
            if (t[v[i]] == 1) {
                t.erase(v[i]);
            } else{
                t[v[i]] -= 1;
            }
        } else {
            if (s.find(v[i]) != s.end()) {
                s[v[i]] += 1;
            } else {
                s[v[i]] = 1;
            }
        }

        if (s.find(u[i]) != s.end()) {
            if (s[u[i]] == 1) {
                s.erase(u[i]);
            } else{
                s[u[i]] -= 1;
            }
        } else {
            if (t.find(u[i]) != t.end()) {
                t[u[i]] += 1;
            } else {
                t[u[i]] = 1;
            }
        }

        if (s.empty()) {
            output += "# ";
        }
    }
    cout << output + to_string(u[N-1]) << endl;
}