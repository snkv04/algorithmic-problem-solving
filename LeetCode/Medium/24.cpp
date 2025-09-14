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
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy;
        dummy.next = head;

        ListNode *last = &dummy, *curr = head;
        while (curr != nullptr && curr->next != nullptr) {
            ListNode *next = curr->next;
            curr->next = curr->next->next;
            next->next = curr;
            last->next = next;

            last = curr;
            curr = curr->next;
        }
        return dummy.next;
    }
};
