#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

#define BIG_NUM 100000000

int main() {
    string initial;
    cin >> initial;
    int n = initial.size();
    ll cost[150];
    int d;
    map<char, int> counts;
    //cout << "ALHJKSDHJLKDFSLHJKSD" << endl;
    for (int i = 0; i < n; i++) {
        counts[initial[i]] += 1;
    }
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    cin >> d;
    for (int i = 0; i < d; i++) {
        int position;
        cin >> position;
        counts[initial[position - 1]] -= 1;
        initial[position - 1] = 'X';
        cost[position - 1] = 0;
    }
    string str;
    cin >> str;
    //cout << str << endl;
    for (char c : str) {
        counts[c] += 1;
    }
    //cout << "HIIIII" << endl;
    map<char, map<int, ll>> cost_to_place;
    for (char c : "AEIOU") {
        cost_to_place[c] = {};
        //cout << c << " ";
        for (int i = 0; i <= n - counts[c]; i++) {
            for (int j = 0; j < counts[c]; j++) {
                if (initial[i + j] != c)
                    cost_to_place[c][i] += cost[i + j];
            }
            //cout << cost_to_place[c][i] << " ";
        }
        //cout << endl;
    }
    //cout << "HI" << endl;
    ll dp[301][2][2][2][2][2];
    for (int pos = 0; pos <= n; pos++) {
        for (int hasA = 0; hasA <= 1; hasA++) {
            for (int hasE = 0; hasE <= 1; hasE++) {
                for (int hasI = 0; hasI <= 1; hasI++) {
                    for (int hasO = 0; hasO <= 1; hasO++) {
                        for (int hasU = 0; hasU <= 1; hasU++) {
                            dp[pos][hasA][hasE][hasI][hasO][hasU] = BIG_NUM;
                        }
                    }
                }
            }
        }
    }
    dp[0][0][0][0][0][0] = 0;
    for (int pos = 0; pos <= n; pos++) {
        for (int hasA = 0; hasA <= 1; hasA++) {
            for (int hasE = 0; hasE <= 1; hasE++) {
                for (int hasI = 0; hasI <= 1; hasI++) {
                    for (int hasO = 0; hasO <= 1; hasO++) {
                        for (int hasU = 0; hasU <= 1; hasU++) {
                            dp[pos + 1][hasA][hasE][hasI][hasO][hasU] = min(dp[pos + 1][hasA][hasE][hasI][hasO][hasU],
                                dp[pos][hasA][hasE][hasI][hasO][hasU] + cost[pos]);
                            if (!hasA) {
                                dp[pos + counts['A']][1][hasE][hasI][hasO][hasU] = min(dp[pos + counts['A']][1][hasE][hasI][hasO][hasU],
                                    dp[pos][hasA][hasE][hasI][hasO][hasU] + cost_to_place['A'][pos]);
                            }
                            if (!hasE) {
                                dp[pos + counts['E']][hasA][1][hasI][hasO][hasU] = min(dp[pos + counts['E']][hasA][1][hasI][hasO][hasU],
                                    dp[pos][hasA][hasE][hasI][hasO][hasU] + cost_to_place['E'][pos]);
                            }
                            if (!hasI) {
                                dp[pos + counts['I']][hasA][hasE][1][hasO][hasU] = min(dp[pos + counts['I']][hasA][hasE][1][hasO][hasU],
                                    dp[pos][hasA][hasE][hasI][hasO][hasU] + cost_to_place['I'][pos]);
                            }
                            if (!hasO) {
                                dp[pos + counts['O']][hasA][hasE][hasI][1][hasU] = min(dp[pos + counts['O']][hasA][hasE][hasI][1][hasU],
                                    dp[pos][hasA][hasE][hasI][hasO][hasU] + cost_to_place['O'][pos]);
                            }
                            if (!hasU) {
                                dp[pos + counts['U']][hasA][hasE][hasI][hasO][1] = min(dp[pos + counts['U']][hasA][hasE][hasI][hasO][1],
                                    dp[pos][hasA][hasE][hasI][hasO][hasU] + cost_to_place['U'][pos]);
                            }
                        }
                    }
                }
            }
        }
    }
    // for (int pos = 0; pos <= n; pos++) {
    //     for (int hasA = 0; hasA <= 1; hasA++) {
    //         for (int hasE = 0; hasE <= 1; hasE++) {
    //             for (int hasI = 0; hasI <= 1; hasI++) {
    //                 for (int hasO = 0; hasO <= 1; hasO++) {
    //                     for (int hasU = 0; hasU <= 1; hasU++) {
    //                         cout << dp[pos][hasA][hasE][hasI][hasO][hasU] << " ";
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     cout << endl;
    // }
    cout << dp[n][1][1][1][1][1] << endl;
}
