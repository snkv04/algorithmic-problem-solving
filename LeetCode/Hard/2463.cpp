class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        vector<vector<long long>> mem(
            factory.size() + 1,
            vector<long long>(robot.size() + 1, 1e15)
        );
        for (int i = 0; i <= factory.size(); ++i) mem[i][0] = 0;
        for (int i = 1; i <= factory.size(); ++i) {
            for (int j = 1; j <= robot.size(); ++j) {
                mem[i][j] = mem[i - 1][j];
                long long cost = 0;
                for (int k = 1; k <= min(factory[i - 1][1], j); ++k) {
                    cost += abs(factory[i - 1][0] - robot[j - k]);
                    mem[i][j] = min(mem[i][j], mem[i - 1][j - k] + cost);
                }
            }
        }
        return mem[factory.size()][robot.size()];
    }
};
