/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct Comparator {
    bool operator()(const ListNode* n1, const ListNode *n2) {
        return n1->val > n2->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // sets up a priority queue filled with the next node to take
        // from each linked list
        priority_queue<ListNode*, vector<ListNode*>, Comparator> pq;
        for (ListNode *node : lists) if (node != nullptr) pq.push(node);

        // repeatedly takes the smallest next node and appends it to the
        // current result list, using a sentinel node for simpler code
        ListNode *dummy = new ListNode(), *curr = dummy;
        while (pq.size()) {
            // gets/selects the next node
            ListNode *node = pq.top();
            pq.pop();

            // appends it to the result
            curr->next = node;
            curr = curr->next;

            // adds the selected node's next node to the prioqueue
            // if it exists
            if (node->next != nullptr) {
                pq.push(node->next);
            }
        }
        return dummy->next;
    }
};
