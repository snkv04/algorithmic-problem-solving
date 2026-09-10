#include <bits/stdc++.h>
using namespace std;

int main() {
    // Pulls in input
    int w;
    cin >> w;

    // Main logic
    // If value of w is an even number AND greater than 2, then output is YES
    // Else, output is NO
    string answer;
    if (w % 2 == 0 && w > 2) {
        answer = "YES";
    } else {
        answer = "NO";
    }
    
    // Pushes out output
    cout << answer << endl;

    return 0;
}
