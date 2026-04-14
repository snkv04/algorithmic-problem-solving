#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ld dL, dW, G, L;
    cin >> dL >> dW >> G >> L;
    L /= 100.0;
    ld W = 1.0 - L;

    // mem[i][j][0] := probability of not having won any prizes if we've played i matches and P = j / 100.0
    // mem[i][j][1] := probability of winning a prize exactly on the i'th match where P = j / 100.0
    ld mem[101][101][2];
    for (int i = 0; i <= 100; ++i) for (int j = 0; j <= 100; ++j) fill(mem[i][j], mem[i][j] + 2, 0);
    mem[0][0][0] = 1.0;
    for (int i = 1; i <= 100; ++i) {
        for (int j = 1; j <= 100; ++j) {
            // lose
            if (j >= dL) {
                if (j == 100) {
                    for (int k = j - dL; k <= j; ++k) {
                        mem[i][j][0] += L * mem[i - 1][k][0];
                    }
                } else {
                    mem[i][j][0] += L * mem[i - 1][j - (int) dL][0];
                }
            }

            // win and no prize
            if (j >= dW) {
                if (j == 100) {
                    for (int k = j - dW; k <= j; ++k) {
                        mem[i][j][0] += W * ((100.0 - k) / 100.0) * mem[i - 1][k][0];
                    }
                } else {
                    mem[i][j][0] += W * ((100.0 - (j - dW)) / 100.0) * mem[i - 1][j - (int) dW][0];
                }
            }

            // win and get prize
            if (j >= dW) {
                if (j == 100) {
                    for (int k = j - dW; k <= j; ++k) {
                        mem[i][j][1] += W * (k / 100.0) * mem[i - 1][k][0];
                    }
                } else {
                    mem[i][j][1] += W * ((j - dW) / 100.0) * mem[i - 1][j - (int) dW][0];
                }
            }
        }
    }

    ld expected_value = 0.0;
    for (int i = 0; i <= 100; ++i) {
        ld prob = 0.0;
        for (int j = 0; j <= 100; ++j) {
            prob += mem[i][j][1];
        }
        expected_value += prob * i;
    }
    ld tail_prob = 0.0;
    for (int j = 0; j <= 100; ++j) {
        tail_prob += mem[100][j][0];
    }
    expected_value += tail_prob * (100 + 1.0 / W);
    
    ld ans = expected_value * 100.0 / G;
    cout << fixed << setprecision(12) << ans << endl;
}
