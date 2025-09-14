/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
private:
    void dfs(Node *current, Node *cloned, unordered_map<int, Node*> &seen) {
        for (Node *next : current->neighbors) {
            int val = next->val;
            if (seen.find(val) == seen.end()) {
                seen[val] = new Node(val);
                dfs(next, seen[val], seen);
            }
            cloned->neighbors.push_back(seen[val]);
        }
    }

public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;

        Node *cloned_root = new Node(1);
        unordered_map<int, Node*> seen = {make_pair(1, cloned_root)};
        dfs(node, cloned_root, seen);
        return cloned_root;
    }
};
