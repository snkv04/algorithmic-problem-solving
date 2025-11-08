#include <bits/stdc++.h>
using namespace std;

set<int> apply(set<int> &pieces, int shift, int flip) {
    set<int> newpieces;
    for (int piece : pieces) {
        int origpiece = piece;

        piece += shift - 1;
        if (origpiece <= 5) {
            piece = (piece % 5) + 1;
        } else if (origpiece <= 10) {
            piece = (piece % 5) + 6;
        } else if (origpiece <= 20) {
            piece = (piece % 10) + 11;
        } else if (origpiece <= 25) {
            piece = (piece % 5) + 21;
        } else {
            piece = (piece % 5) + 26;
        }

        if (flip) {
            piece = 31 - piece;
        }

        newpieces.insert(piece);
    }
    // cout << "\nflip="<<flip<<", shift="<<shift<<"\npieces: ";
    // for (int p : pieces) cout << p << " ";
    // cout << "\nnewpieces: ";
    // for (int p : newpieces) cout << p << " ";
    // cout << "\n";
    return newpieces;
}

void solve() {
    vector<set<int>> pieces(3);
    for (int i = 0; i < 3; ++i) {
        int m;
        cin >> m;
        while (m--) {
            int piece;
            cin >> piece;
            pieces[i].insert(piece);
        }
    }

    if (pieces[0].size() + pieces[1].size() + pieces[2].size() != 30) {
        cout << "No\n";
        return;
    }

    for (int s1 = 0; s1 < 10; ++s1) {
        int shift1 = s1 % 5, flip1 = s1 / 5;
        for (int s2 = 0; s2 < 10; ++s2) {
            int shift2 = s2 % 5, flip2 = s2 / 5;
            vector<set<int>> configuration = {
                pieces[0],
                apply(pieces[1], shift1, flip1),
                apply(pieces[2], shift2, flip2)
            };

            set<int> total;
            for (int i = 0; i < 3; ++i) {
                for (int j : configuration[i]) total.insert(j);
            }
            // cout << "total = "; for (int t : total) cout << t << " "; cout << endl;
            if (total.size() == 30) {
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
}

int main() {
    solve();

    return 0;
}
