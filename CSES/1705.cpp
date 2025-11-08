// not my code

#include <bits/stdc++.h>
using namespace std;

/** @return the block-cut tree of a graph */
vector<vector<int>> biconnected_components(vector<vector<int>> &g,
                                           vector<bool> &is_cutpoint, vector<int> &id) {
	int n = (int)g.size();

	vector<vector<int>> comps;
	vector<int> stk;
	vector<int> num(n);
	vector<int> low(n);

	is_cutpoint.resize(n);

	// Finds the biconnected components
	function<void(int, int, int &)> dfs = [&](int node, int parent, int &timer) {
		num[node] = low[node] = ++timer;
		stk.push_back(node);
		for (int son : g[node]) {
			if (son == parent) { continue; }
			if (num[son]) {
				low[node] = min(low[node], num[son]);
			} else {
				dfs(son, node, timer);
				low[node] = min(low[node], low[son]);
				if (low[son] >= num[node]) {
					is_cutpoint[node] = (num[node] > 1 || num[son] > 2);
					comps.push_back({node});
					while (comps.back().back() != son) {
						comps.back().push_back(stk.back());
						stk.pop_back();
					}
				}
			}
		}
	};

	int timer = 0;
	dfs(0, -1, timer);
	id.resize(n);

	// Build the block-cut tree
	function<vector<vector<int>>()> build_tree = [&]() {
		vector<vector<int>> t(1);
		int node_id = 0;
		for (int node = 0; node < n; node++) {
			if (is_cutpoint[node]) {
				id[node] = node_id++;
				t.push_back({});
			}
		}

		for (auto &comp : comps) {
			int node = node_id++;
			t.push_back({});
            cout << "comp: ";
			for (int u : comp) {
                cout << u << " ";
                if (!is_cutpoint[u]) {
					id[u] = node;
				} else {
					t[node].push_back(id[u]);
					t[id[u]].push_back(node);
				}
            }
            cout << endl;
		}
		return t;
	};

	return build_tree();
}

int main() {
	int n, m, q;
	cin >> n >> m >> q;

	const int LOGMAX = (int)ceil(log2(n));
	vector<vector<int>> g;
	g.resize(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}
    for (int i = 0; i < n; ++i) {
        cout << "g[" << i << "]: ";
        for (int next : g[i]) cout << next << " ";
        cout << endl;
    }

	vector<int> id, depth(3 * n, 0);
	vector<bool> is_cutpoint;
	vector<vector<int>> up(3 * n, vector<int>(LOGMAX));
	vector<vector<int>> blockcut_tree = biconnected_components(g, is_cutpoint, id);
    cout << "bct.size() = " << blockcut_tree.size() << "\n";
    for (int i = 0; i < blockcut_tree.size(); ++i) {
        cout << "bct[" << i << "]: ";
        for (int j : blockcut_tree[i]) cout << j << " ";
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        cout << "id[" << i << "] = " << id[i] << endl;
    }
    for (int i = 0; i < n; ++i) {
        cout << "is_cutpoint[" << i << "] = " << is_cutpoint[i] << endl;
    }

	// Compute the LCA
	function<void(int, int)> dfs = [&](int node, int parent) {
		if (parent != -1) {
			depth[node] = depth[parent] + 1;
			up[node][0] = parent;
			for (int j = 1; j < LOGMAX; j++) {
				up[node][j] = up[up[node][j - 1]][j - 1];
			}
		}
		for (auto son : blockcut_tree[node]) {
			if (son == parent) continue;
			dfs(son, node);
		}
	};

	auto find_lca = [&](int x, int y) {
		if (depth[x] < depth[y]) { swap(x, y); }
		int diff = depth[x] - depth[y];
		for (int i = LOGMAX; i >= 0; i--) {
			if ((1 << i) & diff) { x = up[x][i]; }
		}
		if (x == y) { return x; }
		for (int i = LOGMAX; i >= 0; i--) {
			if (up[x][i] != up[y][i]) {
				x = up[x][i];
				y = up[y][i];
			}
		}
		return up[x][0];
	};

	// Check whether the node z is on path (x, y)
	auto on_path = [&](int x, int y, int z) {
		int lca = find_lca(x, y);
		int lca1 = find_lca(x, z);
		int lca2 = find_lca(y, z);

		if (lca == z || (lca1 == lca && lca2 == z) || (lca2 == lca && lca1 == z)) {
			return true;
		}
		return false;
	};

	dfs(0, -1);

	for (int i = 0; i < q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--, c--;
		// The path does not exist in two cases:
		// 1) a == c or b == c
		// 2) c is a cutpoint and it lies on path between a and b in block-cut
		// tree
		if (a == c || b == c || (is_cutpoint[c] && on_path(id[a], id[b], id[c]))) {
			std::cout << "NO\n";
		} else {
			cout << "YES" << '\n';
		}
	}
}
