class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        int cnt = 0;
        int lx = location[0], ly = location[1];
        vector<long double> angles;
        for (int i = 0; i < points.size(); ++i) {
            int x = points[i][0], y = points[i][1];
            if (x == lx && y == ly) {
                ++cnt;
                continue;
            }

            long double degrees = (long double) std::atan2(y - ly, x - lx) * (180.0 / std::numbers::pi);
            angles.push_back(degrees);
            angles.push_back(degrees + 360);
        }
        std::sort(angles.begin(), angles.end());

        int ans = 0, i = 0;
        cout << fixed << setprecision(12);
        for (int j = 0; j < angles.size(); ++j) {
            while (angles[j] - angles[i] > angle + 1e-9) ++i;
            ans = max(ans, j - i + 1);
        }
        ans += cnt;
        return ans;
    }
};
