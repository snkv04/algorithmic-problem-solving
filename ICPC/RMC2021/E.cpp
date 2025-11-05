#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    int N;
    cin >> N;
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> v[i];
    }
    
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 0; i < N; ++i)
    {
        if (i < (N / 2 + 1))
        {
            ans += (v[i] / 2);
        }
        else
        {
            ans += v[i];
        }
    }
    cout << ans;
}