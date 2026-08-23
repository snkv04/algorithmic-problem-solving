#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

struct Strategy {
    int strategyId;
    int typeId;
    int position;
};

struct StrategyComparator {
    bool operator()(const Strategy &s1, const Strategy &s2) const {
        if (s1.typeId != s2.typeId) {
            return s1.typeId < s2.typeId;
        } else {
            return s1.position < s2.position;
        }
    }
};

class StrategyRegistry {
private:
    std::set<Strategy, StrategyComparator> strategies;
    std::unordered_map<int, int> sid_to_tid;
    int timer = 0;

public:
    void registerStrategy(int strategyId, int typeId) {
        strategies.insert(Strategy{strategyId, typeId, timer++});
        sid_to_tid[strategyId] = typeId;
    }

    std::vector<int> warmUp() {
        std::vector<int> result;
        for (const Strategy &s : strategies) {
            result.push_back(s.strategyId);
        }
        return result;
    }

    int getType(int strategyId) {
        if (sid_to_tid.count(strategyId)) {
            return sid_to_tid[strategyId];
        } else {
            return -1;
        }
    }
};
