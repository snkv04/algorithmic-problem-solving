using ll = long long;

struct Comp {
    bool operator()(const pair<ll, int> &first, const pair<ll, int> &second) {
        if (first.first != second.first) {
            return first.first > second.first;
        } else {
            return first.second > second.second;
        }
    }
};

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(
            meetings.begin(),
            meetings.end(),
            [](const vector<int> &a, const vector<int> &b) {
                return a[0] < b[0];
            }
        );
        
        vector<int> num_meetings(n, 0);
        set<int> available; for (int i = 0; i < n; ++i) available.insert(i);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, Comp> active_meetings;
        for (auto &meeting : meetings) {
            // jumped to meeting start time, so wrap up all finished meetings
            ll start = meeting[0], length = meeting[1] - start;
            while (active_meetings.size() && active_meetings.top().first <= start) {
                available.insert(active_meetings.top().second);
                active_meetings.pop();
            }

            // if no rooms are available, skip to next time when room will become free
            // 
            // TODO: figure out why commenting out the code below actually works???
            // if we wait for a room to become empty, then wouldn't all of the rooms
            // that end at that time become empty at the same time? sure, that might
            // result in jumping forward to a time when a bunch of rooms empty up then
            // jumping backward to a time when the next meeting to be processed begins,
            // but i don't think that would be wrong, because that meeting would also
            // have been waiting for the same time to occur (or later) so that a room
            // would be free for it?
            if (available.empty()) {
                assert(active_meetings.size() == n);
                start = active_meetings.top().first;
                // while (
                //     active_meetings.size() &&
                //     active_meetings.top().first == start
                // ) {
                    available.insert(active_meetings.top().second);
                    active_meetings.pop();
                // }
            }

            // book meeting
            int room = *available.begin();
            active_meetings.push(make_pair(start + length, room));
            available.erase(room);
            num_meetings[room] += 1;
        }
        // for (int i = 0; i < n; ++i) {
        //     cout << "num_meetings[" << i << "] = " << num_meetings[i] << endl;
        // }
        
        int max_usage = 0;
        for (int i = 0; i < n; ++i) max_usage = max(max_usage, num_meetings[i]);

        for (int i = 0; i < n; ++i) {
            if (num_meetings[i] == max_usage) {
                return i;
            }
        }
        throw std::logic_error("num_meetings array is inconsistent");
    }
};
