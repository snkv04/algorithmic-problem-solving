#include <bits/stdc++.h>
using namespace std;

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode*> ptrs;
        ListNode *curr = head;
        while (curr != nullptr) {
            ptrs.push_back(curr);
            curr = curr->next;
        }
        ptrs.push_back(nullptr);

        int sz = ptrs.size() - 1;
        n = sz - n;
        if (n == 0) {
            if (sz == 1) {
                return nullptr;
            } else {
                return ptrs[1];
            }
        } else {
            ptrs[n - 1]->next = ptrs[n + 1];
            return head;
        }
    }
};
