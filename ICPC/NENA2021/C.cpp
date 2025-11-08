#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

bool all_equal(map<int, int>& m)
{
    int common = -1;
    for (auto element : m)
    {
        if (common == -1)
        {
            common = element.first;
        }
        if (element.first != common)
        {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        string s;
        cin >> s;
        int len = s.length();
        map<int, int> m;
        vector<bool> valid(7);

        if (len < 7)
        {
            if (all_equal(m))
            {
                cout << 
            }
        }
        // check the first window
        for (int i = 0; i < 7; ++i)
        {
            ++m[s[i]];
        }
        valid[0] = all_equal(m);
        
    }
}