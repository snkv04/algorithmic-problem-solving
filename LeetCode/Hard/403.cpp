class Solution {
public:
    bool canCross(vector<int>& stones) {
        map<int, set<int>> ways;
        for (int stone : stones) {
            ways[stone] = set<int>();
        }
        ways[0].insert(0);

        for (auto it = ways.begin(); it != ways.end(); ++it) {
            for (int last_jump : it->second) {
                array<int, 3> next_jumps = {
                    last_jump - 1,
                    last_jump,
                    last_jump + 1
                };
                for (int jump : next_jumps) {
                    if (jump > 0 && ways.count(it->first + jump)) {
                        ways[it->first + jump].insert(jump);
                    }
                }
            }
        }
        int target = stones[stones.size() - 1];
        return ways[target].size();
    }
};
