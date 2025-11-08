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
    map<char, int> m1;
    for (int i = 0; i < slen; ++i)
    {
        ++m1[s[i]];
    }

    // find minLen
    int minLen = INT_MAX;
    bool didBreak3 = false;
    for (int i = 0; i < vlen; ++i)
    {
        if (m1.find(v[i]) == m1.end())
        {
            minLen = 1;
            didBreak3 = true;
            break;
        }
    }
    if (!didBreak3)
    {
        unordered_map<char, bool> visited;
        int visited_count = 0;
        int len_sub = 0;
        for (char c : v) {
            visited[c] = false;
        }
        for (char c : s) {
            if (!visited[c]) {
                visited[c] = true;
                visited_count++;
                if (visited_count == v.length()) {
                    len_sub++;
                    visited_count = 0;
                    for (char c : v) {
                        visited[c] = false;
                    }
                }
            }
        }
        len_sub++;
        minLen = len_sub;
    }
    // cout << "minlen " << minLen << endl;

    // precompute
    vector<map<char, int>> precompute(slen);
    map<char, int> lastOne;
    for (int j = 0; j < vlen; ++j)
    {
        lastOne[v[j]] = -1;
    } 
    precompute[slen - 1] = lastOne;

    char lastChar = s[slen - 1];
    for (int i = slen - 2; i >= 0; --i)
    {
        map<char, int> temp = precompute[i + 1];
        temp[lastChar] = i + 1;
        lastChar = s[i];
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

        // need all the characters in query to be in s
        map<char, int> m2;
        for (int i = 0; i < qlen; ++i)
        {
            ++m2[q[i]];
        }
        bool didBreak = false;
        for (auto element : m2)
        {
            char key = element.first;
            if (m2[key] > m1[key])
            {
                cout << "0" << endl;
                didBreak = true;
                break;
            }
        }
        if (didBreak)
        {
            continue;
        }

        // need to check if everything was in order
        int counter = 0;
        bool didBreak2 = false;
        for (int i = 0; i < slen; ++i)
        {
            if (counter == qlen)
            {
                cout << "0" << endl;
                didBreak2 = true;
                break;
            }
            if (s[i] == q[counter])
            {
                ++counter;
            }
        }
        if (!didBreak2 && counter < qlen)
        {
            cout << "1" << endl;
        }
    }
}