class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<int> people(n, 0);
        people[0] = 1;
        for (int i = 0; i < n-1; ++i) {
            int start = i + delay, end = i + forget;
            if (start >= n) break;

            for (int j = start; j < min(end, n); ++j) {
                people[j] += people[i];
                people[j] %= static_cast<int>(1e9 + 7);
            }
        }

        int ans = 0;
        for (int i = n - forget; i < n; ++i) {
            ans += people[i];
            ans %= static_cast<int>(1e9 + 7);
        }
        return ans;
    }
};
