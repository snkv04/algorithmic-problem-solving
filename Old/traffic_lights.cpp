#include <iostream>
#include <set>
#include <vector>
#include <stack>

using namespace std;

void solve() {
    int n, x;
    cin >> x >> n;
    int lights[n];
    set<int> sorted;
    sorted.insert(0); sorted.insert(x);
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        lights[i] = p;
        sorted.insert(p);
    }

    int last = 0, longest = 0;
    for (auto light : sorted) {
        longest = max(longest, light - last);
        last = light;
    }

    stack<int> ans;
    ans.push(longest);
    for (int i = n-1; i >= 0; --i) {
        int light = lights[i];
        longest = max(longest, *sorted.upper_bound(light) - *(--sorted.lower_bound(light)));
        sorted.erase(sorted.find(light));
        if (i) {
            ans.push(longest);
        }
    }

    while (!ans.empty()) {
        int l = ans.top();
        ans.pop();
        cout << l << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}