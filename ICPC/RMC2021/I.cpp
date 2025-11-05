#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    int N;
    int C;
    int s = 1;
    int e = 1;
    cin >> N >> C;
    vector<int> v(N + 1);
    for (int i = 1; i <= N; ++i)
    {
        cin >> v[i];
    }
    int sum = v[1];
    vector<int> ans(N);
    vector<pair<int, int>> windows;
    while (s <= N)
    {
        if (sum <= C)
        {
            // cout << "s, e: " << s << " " << e << endl;
            // for (int i = s - 1; i <= e - 1; ++i)
            // {
            //     ++ans[i];
            // }
            if (s <= e)
            {
                windows.push_back({s, e});
            }
        }
        // cout << "sum: " << sum << endl;
        if (e + 1 > N)
        {
            sum -= v[++s];
        }
        else if (sum + v[e + 1] > C)
        {
            sum -= v[s++];
        }
        else
        {
            sum += v[++e];
        }
    }

    int windowSize = windows.size();
    map<int, int> m;

    // backward pass
    for (int i = windowSize - 1; i >= 0; --i)
    {
        if (m.find(windows[i].first) == m.end())
        {
            m[windows[i].first] = i;
        }
    }

    // for (const pair<int, int> &entry : m)
    // {
    //     int val = entry.second;
    //     cout << val << endl;
    // }
    // cout << endl;

    // forward pass
    vector<bool> visited(N, false);
    for (int i = 0; i < windowSize; ++i)
    {
        if (!visited[windows[i].second])
        {
            m[windows[i].second] -= i;
            visited[windows[i].second] = true;
        }
    }

    for (const pair<int, int> &entry : m)
    {
        int val = entry.second + 1;
        cout << val << endl;
    }
}