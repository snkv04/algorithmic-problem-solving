#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> count(k, 0);
        set<int> available_servers;
        for (int i = 0; i < k; ++i) available_servers.insert(i);
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> events;
        for (int i = 0; i < arrival.size(); ++i) {
            int arrival_time = arrival[i], length = load[i];

            // process all events
            while (events.size() && events.top().first <= arrival_time) {
                auto [finish_time, server] = events.top();
                events.pop();
                available_servers.insert(server);
            }

            // find server
            if (available_servers.size()) {
                int server = available_servers.lower_bound(i % k) == available_servers.end()
                    ? *available_servers.begin()
                    : *available_servers.lower_bound(i % k);
                available_servers.erase(server);
                count[server] += 1;
                events.push(make_pair(arrival_time + length, server));
            }
        }

        int max_count = 0;
        for (int i = 0; i < k; ++i) {
            max_count = max(max_count, count[i]);
        }

        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (count[i] == max_count) {
                result.push_back(i);
            }
        }
        return result;
    }
};
