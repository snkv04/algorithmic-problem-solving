/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
private:
    void process(Node *node) {
        if (node->left == nullptr) {
            return;
        }

        node->left->next = node->right;
        if (node->next == nullptr) {
            node->right->next = nullptr;
        } else {
            node->right->next = node->next->left;
        }
        process(node->left);
        process(node->right);
    }

public:
    Node* connect(Node* root) {
        /*
        - there are two common approaches for tree problems where the tree is
        rooted. either you do the subtrees first, and then deal with the root,
        or deal with the parent first, and then use the parent's information
        to fill in information for the children.

        this is done in two ways: either, for a given node, we point to the
        parent, so that we can traverse back up and get information from the
        parent node in order to fill in the current node, or on each node, we
        fill in information about the child nodes. in this case, we are doing
        the latter.
        */
        
        if (root == nullptr) {
            return root;
        }

        root->next = nullptr;
        process(root);
        return root;
    }
};
