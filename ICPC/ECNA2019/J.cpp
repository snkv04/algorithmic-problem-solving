#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<ll, ll>> books;
ll n, m;

#define INF 100000000;
//ll dp[100000][100000];

// returns true if there is a valid reading order
bool check(ll speed) {
    //cout << "speed: " << speed << endl;
    priority_queue<ll> pq;
    ll skips = 0;
    ll pages = 0;
    for (auto book : books) {
        //cout << "P " << pages << endl;
        pages += book.second;
        pq.push(book.second);
        if (pages > book.first * speed) {
            skips++;
            pages -= pq.top();
            pq.pop();
        }
    }
    return (skips <= m);

    // for (int i = 0; i <= books.size(); i++) {
    //     for (int j = 0; j <= m; j++) {
    //         dp[i][j] = INF;
    //     }
    // }
    // dp[0][0] = 0;
    // for (int pos = 0; pos <= books.size(); pos++) {
    //     for (int used = 0; used <= m; used ++) {
    //         //skip
    //         dp[pos][used + 1] = min(dp[pos][used + 1], dp[pos][used]);

    //         //read
    //         if (books[pos].first * speed >= books[pos].second + dp[pos][used]) {
    //             dp[pos + 1][used] = min(dp[pos + 1][used], books[pos].second + dp[pos][used]);
    //         }
    //     }
    // }
    // return dp[n][m] < INF;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        pair<ll, ll> p;
        cin >> p.second >> p.first;
        books.push_back(p);
    }
    sort(books.begin(), books.end());

    ll low = 1, high, ans;
    for (int i = 0; i < n; ++i) {
        high += books[i].second;
        ans = high;
    }
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans << endl;

    return 0;
}
