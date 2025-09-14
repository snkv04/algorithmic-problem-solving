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
public:
    Node* connect(Node *root) {
        /*
        in the default implementation, we do a simple BFS approach. namely,
        we keep a list of nodes on the current level, and for each level,
        we gather all of the nodes from the next level in order, and set
        each adjacent pair to have the first's "next" point to the second.

        a core idea in this problem is to set the "next" pointer for the
        next/below level while traversing through the current level.

        the memory-efficient solution works very similarly to the brute-force
        approach. first, we have a variable pointing to the leftmost element
        on the current level. remember, we are assuming that the current level
        already has its "next" pointers filled in, which (just like in proofs
        by induction) is already true for the root node. now, we walk through
        the current level, keeping track of both the pointer for the current
        level which was previously mentioned as well as a pointer for the
        next level, and whenever there is a node at the next level, we set
        the next level ptr's "next" value to that node, and push the next
        level ptr to be that node (so that it effectively traverses that
        level horizontally). finally, after we're done walking through the
        current level, we set the leftmost element of the current level to be
        the leftmost element of the next level. why leftmost? this allows us
        to walk through each level in order.

        in short, we are getting rid of the need for a queue at each level
        by just explicitly keeping track of the last-pushed element of the
        queue at each level (current level and next level). at the beginning
        of a level, the "last-pushed" element of the next level doesn't exist
        yet, which is why we need a dummy node.

        why do we have "curr_level_ptr != nullptr" twice? the outer loop checks
        that we are not out of levels. we iterate vertically, and when we are
        done with levels, then curr_level_ptr is nullptr. the inner loop checks
        that we are not out of nodes at the current level. we iterate through
        nodes horizontally, and it finishes when we try to move to the
        "next" node at the current level and that node is nullptr (to the
        right side of the tree.)
        */

        if (root == nullptr) return nullptr;

        // initialize a "current level" pointer node to just be the root
        Node *curr_level_ptr = root;
        while (curr_level_ptr != nullptr) {
            // make a dummy node, representing the thing right before
            // the leftmost node on the next level, as well as a ptr
            // to traverse through the next level
            Node *next_level_dummy = new Node();
            Node *next_level_ptr = next_level_dummy;

            // traverse through the nodes on the current level (keep in
            // mind that the current level's "next" ptrs are already filled
            // in, so we can just walk through them). the point of this is
            // to fill in the "next" ptrs on the next level
            while (curr_level_ptr != nullptr) {
                // go through the two children for the current-level node,
                // and whatever the most recently-looked at node on the
                // next level is (even if it's the dummy), set its next ptr
                // to the child node(s), moving over the next level's ptr
                // to traverse that child node
                if (curr_level_ptr->left != nullptr) {
                    next_level_ptr->next = curr_level_ptr->left;
                    next_level_ptr = curr_level_ptr->left;
                }
                if (curr_level_ptr->right != nullptr) {
                    next_level_ptr->next = curr_level_ptr->right;
                    next_level_ptr = curr_level_ptr->right;
                }
                curr_level_ptr = curr_level_ptr->next;
            }

            // now, initialize the curr level ptr to be the leftmost
            // node on the next level (which there might be none of, in
            // which case we are done)
            curr_level_ptr = next_level_dummy->next;
        }
        return root;
    }
};
