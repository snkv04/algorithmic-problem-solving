#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int n, k;
vector<string> answers;
unordered_set<int> unvisited;
string ans;

void printstate() {
    cout << "unvisited: ";
    for (int i : unvisited) {
        cout << i << " ";
    }
    cout << endl;

    cout << "ans: " << ans << endl;
}

bool tryset(int i , char c) {
    if (ans[i] == c) return true;
    if (ans[i] != ' ') return false;
    ans[i] = c;
    vector<pair<int, char>> to_set;
    unordered_set<int> unvisited_new = unvisited;
    for (int student : unvisited) {
        //cout << "student: " << student << endl;
        if (answers[student][i] == c) {
            unvisited_new.erase(student);
            for (int j = 0; j < k; j++) {
                if (i == j) continue;
                if (answers[student][j] == 'T') {
                    to_set.push_back({j, 'F'});
                }
                if (answers[student][j] == 'F') {
                    to_set.push_back({j, 'T'});
                }
            }
        }
    }
    unvisited = unvisited_new;

    //printstate();
    //for (pair<int, char> p : to_set) {
    //    cout << p.first << " " << p.second << endl;
    //}


    for (pair<int, char> p : to_set) {
        //cout << "now on " << p.first << " " << p.second << endl;
        if (!tryset(p.first, p.second)) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> k;
    ans = string(n, ' ');
    for (int i = 0; i < n;i++){
        string s;
        cin >> s;
        answers.push_back(s);
    }
    for (int i = 0; i < n; i++) {
        unvisited.insert(i);
    }

    for (int i = 0; i < k; i++) {
        if (ans[i] != ' ') continue;
        unordered_set<int> unvisited_cp = unvisited;
        string ans_cp = ans;
        if (tryset(i, 'F')) continue;
        unvisited = unvisited_cp;
        ans = ans_cp;
        if (tryset(i, 'T')) continue;
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
}