#include <bits/stdc++.h>
using namespace std;

vector<char> dirs = {'E', 'S', 'W', 'N'};
map<char, int> to_num = {
    {'E', 0},
    {'S', 1},
    {'W', 2},
    {'N', 3}
};
map<char, char> flipped = {
    {'E', 'W'},
    {'W', 'E'},
    {'N', 'S'},
    {'S', 'N'},
};

int n, m;
vector<vector<pair<int, int>>> by_dir; // for each (node, outgoing dir) pair, holds (next_node, weight)
vector<map<int, pair<int, int>>> by_node; // for each (node, outgoing node) pair, holds (dir_to_next_node, weight)
vector<pair<int, char>> stk; // holds (node, currently_going_dir) pairs, basically representing edges that have been traversed
set<pair<int, char>> on_stack;
vector<vector<int>> loc;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

// returns (next_node, dir_to_next_node)
pair<int, char> pick_next(int node, char from) {
    int from_num = to_num[from];
    vector<pair<int, int>> valid;
    for (int i = 1; i <= 3; ++i) {
        int next_num = (from_num + 2 + i) % 4;
        if (by_dir[node][next_num].first != -1) {
            valid.push_back(make_pair(by_dir[node][next_num].first, next_num));
        }
    }

    if (valid.empty()) {
        return make_pair(-1, ' ');
    } else if (valid.size() == 1 || valid.size() == 2) {
        return make_pair(valid[0].first, dirs[valid[0].second]);
    } else {
        return make_pair(valid[1].first, dirs[valid[1].second]);
    }
}

void traverse_forward(int node, int next, char dir, int times) {
    int dir_num = to_num[dir];
    by_dir[node][dir_num].second -= times;
    if (by_dir[node][dir_num].second == 0) {
        by_dir[node][dir_num].first = -1;
        by_node[node].erase(next);
    } else {
        by_node[node][next].second -= times;
    }
}

void traverse(int node, int next, char dir, int times) {
    traverse_forward(node, next, dir, times);
    dir = flipped[dir];
    traverse_forward(next, node, dir, times);
}

void solve() {
    /*
    - the brute-force solution is to simulate the entire path from beginning to end. however, since
    m <= 4 * n = 10000, this could be up to O(m * maxk) = O(1e4 * 1e6) = O(1e10), which is too slow.
    (actually, maxm is 4900 from the worst case, but this is asymptotically basically identical.)
    so, what we can do to speed this up is simulate up until we find that we have gone through a cyclical
    path, then "fast-forward" through the cycle until we can't go on that cycle anymore, then start
    simulating again. why does this work? each time we fast-forward through a cycle, at least one edge
    on the cycle drops to interest level 0 (or interest level 1, as discussed below when talking about
    doubly-traversed edges), so the number of times we need to find cycles is equal to (possibly twice,
    but that's asymptotically the same) the number of edges. the length of a cycle is up to double the
    number of vertices (due to going both ways on almost every edge), so this is O(2n * maxm) = O(n^2),
    which is sufficient.
        - we keep track of the visitation history in a stack, so any edge that we traversed (since processing
        the last cycle) will be in the stack. this is important because it means that if we ever encounter a
        cycle (step onto the same edge in the same direction twice), we can retrace our steps back to where
        we just went to.
        - we need to be careful in detecting cycles. simply arriving at the same node twice is not a sufficient
        condition, because we might have gotten to the node and gone in a different direction the second time
        compared to the first time. instead, we need to either keep track of the edges we traverse (and the
        direction that we traversed them in), or keep track of the nodes we traverse along with either the direction
        we're going in from there or the direction we got to that node from. that ensures that we will take the
        same path the next time UNDER THE ASSUMPTION that no edges were deleted.
        - however, even if an edge on that path was deleted, this logic will still work, because then the minimum
        ((remaining interest) / (num times stepped on edge)) will just be 0, so the number of times that we
        fast-forward through that cycle will just be 0.
        - a relatively difficult-to-find edge case: we might step onto the same edge twice but in opposite directions,
        and this is interesting because if we end up fast-forwarding a cycle where both traversals are included
        in the cycle, then to count the number of times we will fast-forward it, we must consider the fact that
        the edge's interest level will go down twice for every run of the cycle. how do we generalize this to
        remember this, in the case that something similar appears in future problems? every bidirectional edge
        can be traversed twice. more generally, for any given object, recognize that the number of ways that
        an operation can be performed on it might be more than 1; 2 is just a special case.

    generalizable ideas for the future:
    - if a function modifies some variables (such as possibly deleting an adjacent edge from a node
    in a graph), but we need to keep track of the original values of those variables, then make sure to
    extract those values first. more generally, if calling a function, consider if that function might modify
    any of the variables that we use after the function call has finished running, because it could end up
    causing behavior that we don't want.
    - to pick which direction we go in, we keep track of all 4 directions sorted in the order that allows us to
    make the easiest decision later on, and iterate through them by modding by 4. if we're coming to a node by
    going in the N direction, then the sorted order of the directions we can go in is W, N, E. the general rule
    for figuring out how to do these things is: try to make the simplest possible model of the situation that
    catches the maximum number of cases. in this case, we can model the 4 edges for each node in an array, and
    this lets us use the exact same code (iterate through the 3 edges that we can possibly go through, construct
    a list of the valid ones, use that list of valid edges for deciding direction) for every direction.
    - in this problem, we start at a node and have an initial direction, meaning that our second node is
    deterministic. in general, consider which information is basically determined from the input immediately
    and which information needs to follow the looping computation used for everything else later on. if it's
    easier (though possibly less elegant) to just manually catch more edge cases than needed at the beginning,
    then just do that (so your code is correct), and then modify it later if it can be made cleaner by letting
    the edge case be caught through your general-case code.
    */

    // reads in nodes
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        loc.push_back(vector<int>({x, y}));
    }

    // reads in edges
    by_dir.resize(n); by_node.resize(n);
    for (int i = 0; i < n; ++i) {
        by_dir[i].resize(4);
        fill(by_dir[i].begin(), by_dir[i].end(), make_pair(-1, 0));
    }
    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;
        --i; --j;
        if (loc[i][0] == loc[j][0]) {
            if (loc[i][1] > loc[j][1]) swap(i, j);

            // north edge
            by_dir[i][3] = make_pair(j, k);
            by_node[i][j] = make_pair(3, k);

            // south edge
            by_dir[j][1] = make_pair(i, k);
            by_node[j][i] = make_pair(1, k);
        } else {
            if (loc[i][0] > loc[j][0]) swap(i, j);

            // east edge
            by_dir[i][0] = make_pair(j, k);
            by_node[i][j] = make_pair(0, k);

            // west edge
            by_dir[j][2] = make_pair(i, k);
            by_node[j][i] = make_pair(2, k);
        }
    }

    // initializes path
    int s;
    char d;
    cin >> s >> d;
    --s;
    stk.push_back(make_pair(s, ' ')); // didn't come from anywhere
    on_stack.insert(make_pair(s, ' ')); // didn't come from anywhere
    
    // first edge
    int nexts = by_dir[s][to_num[d]].first; // just make it a separate variable for clarity
    traverse(s, nexts, d, 1); // has to be after getting the next node, because traverse() might delete the edge
    stk.push_back(make_pair(nexts, d));
    on_stack.insert(make_pair(nexts, d));

    // simulates path
    while (true) {
        pair<int, char> state = stk.back();
        pair<int, char> next = pick_next(state.first, state.second);
        if (next.first == -1) {
            break;
        }

        if (on_stack.find(next) != on_stack.end()) {
            // find what gets cycled
            int idx = 0;
            while (stk[idx] != next) {
                ++idx;
            }

            // make the stack be just the cycle
            // O(n) for the erasure is fine, since this entire block of code will be O(n) anyway
            stk.erase(stk.begin(), stk.begin() + idx);

            // find num times it repeats by:
            // (1) finding num times each edge is traversed (either once or twice)
            // (2) taking minimum value of (remaining interest / num times was traversed)
            map<pair<int, int>, int> edge_count;
            for (int i = 0; i < stk.size(); ++i) {
                int curr_node = stk[i].first, next_node = stk[(i+1)%stk.size()].first;
                if (curr_node > next_node) swap(curr_node, next_node);
                edge_count[make_pair(curr_node, next_node)] += 1; // canonicalize and increment count
            }
            int num_times = 1e9;
            for (int i = 0; i < stk.size(); ++i) {
                int curr_node = stk[i].first, next_node = stk[(i+1)%stk.size()].first;
                if (curr_node > next_node) swap(curr_node, next_node);
                num_times = min(num_times, by_node[curr_node][next_node].second / edge_count[make_pair(curr_node, next_node)]);
            }

            // simulate all runs through the cycle
            for (int i = 0; i < stk.size(); ++i) {
                int curr_node = stk[i].first, next_node = stk[(i+1)%stk.size()].first;
                char direction = stk[(i+1)%stk.size()].second;
                traverse(curr_node, next_node, direction, num_times);
            }

            // remove all nodes from the stack
            stk.clear();
            on_stack.clear();

            // place us back at the last spot
            stk.push_back(state);
            on_stack.insert(state);
        } else {
            traverse(state.first, next.first, next.second, 1);
            stk.push_back(next);
            on_stack.insert(next);
        }
    }
    
    int final_node = stk.back().first;
    cout << loc[final_node][0] << ' ' << loc[final_node][1] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
