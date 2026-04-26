struct Comparator {
    bool operator()(const array<int, 4> &a, const array<int, 4> &b) const {
        return a[1] < b[1];
    }
};

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        set<array<int, 4>, Comparator> robots;
        int n = directions.size();
        for (int i = 0; i < n; ++i) {
            array<int, 4> robot = {i, positions[i], healths[i], directions[i] == 'R'};
            robots.insert(robot);
        }

        priority_queue<tuple<double, int, int>> collisions;
        for (auto [idx, pos, health, dir] : robots) {
            if (dir == 1) {
                auto it = robots.upper_bound({idx, pos, health, dir});
                if (it != robots.end() && (*it)[3] == 0) {
                    auto [nidx, npos, nhealth, ndir] = *it;
                    double time = (npos - pos) / 2.0;
                    collisions.push({-time, idx, nidx});
                }
            }
        }

        while (collisions.size()) {
            auto [time, i1, i2] = collisions.top();
            collisions.pop();
            time *= -1;
            int idx1 = i1, idx2 = i2;

            if (healths[idx1] == healths[idx2]) {
                healths[idx1] = healths[idx2] = 0;
                robots.erase({-1, positions[idx1], -1, -1});
                robots.erase({-1, positions[idx2], -1, -1});

                auto it = robots.upper_bound({-1, positions[idx1], -1, -1});
                if (it != robots.end() && it != robots.begin()) {
                    int idx4 = (*it)[0];
                    --it;
                    int idx3 = (*it)[0];
                    if (directions[idx3] == 'R' && directions[idx4] == 'L') {
                        double time = (positions[idx4] - positions[idx3]) / 2.0;
                        collisions.push({-time, idx3, idx4});
                    }
                }
            } else {
                if (healths[idx1] < healths[idx2]) {
                    swap(idx1, idx2);
                }

                --healths[idx1];
                healths[idx2] = 0;
                robots.erase({-1, positions[idx2], -1, -1});
                if (directions[idx1] == 'R') {
                    auto it = robots.upper_bound({-1, positions[idx1], -1, -1});
                    if (it != robots.end()) {
                        auto [otheridx, p, h, d] = *it;
                        if (d == 0) {
                            double time = (p - positions[idx1]) / 2.0;
                            collisions.push({-time, idx1, otheridx});
                        }
                    }
                } else {
                    auto it = robots.lower_bound({-1, positions[idx1], -1, -1});
                    if (it != robots.begin()) {
                        --it;
                        auto [otheridx, p, h, d] = *it;
                        if (d == 1) {
                            double time = (positions[idx1] - p) / 2.0;
                            collisions.push({-time, idx1, otheridx});
                        }
                    }
                }
            }
        }

        vector<int> result;
        for (int i = 0; i < n; ++i) if (healths[i]) result.push_back(healths[i]);
        return result;
    }
};
