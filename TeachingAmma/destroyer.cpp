#include <bits/stdc++.h>
using namespace std;

string solve(vector<int> &claims) {
    // Observations:
    // - If n different robots all claim that k robots are in front of them,
    // then those robots need to stand in n different rows,
    // so the total number of rows must be >= n
    // - As the index increases (or moves right) in the count array,
    // the related element has to be equal to or less than the previous element

    // Sort claims in ascending order
    sort(claims.begin(), claims.end());

    // Create count array and fill it in
    int max_claim = 0;
    for (int i = 0; i < claims.size(); ++i) max_claim = max(max_claim, claims[i]);
    vector<int> counts(max_claim + 1, 0);
    for (int claim : claims) {
        counts[claim] = counts[claim] + 1;
    }

    // For each element, it has to be equal to or less than the previous element
    string output = "YES";
    for (int index = 1; index < counts.size(); ++index) {
        if (counts[index] > counts[index - 1]) {
            output = "NO";
            break;
        }
    }
    return output;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> claims(n);
        for (int i = 0; i < n; ++i) {
            cin >> claims[i];
        }
        cout << solve(claims) << endl;
    }

    return 0;
}
