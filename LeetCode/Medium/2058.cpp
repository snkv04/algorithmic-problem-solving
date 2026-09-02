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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int idx = 0;
        int prev_prev = -1, prev = -1;
        int last = -1, mn = 1e9;
        int first_critical_idx = -1, last_critical_idx = -1;
        while (head != nullptr) {
            int curr = head->val;
            if (
                prev_prev != -1 &&
                ((prev > prev_prev && prev > curr) || (prev < prev_prev && prev < curr))
            ) {
                int critical_idx = idx - 1;

                if (last != -1) {
                    int dist = critical_idx - last;
                    mn = min(mn, dist);
                }
                last = critical_idx;

                if (first_critical_idx == -1) {
                    first_critical_idx = critical_idx;
                }
                last_critical_idx = critical_idx;
            }

            ++idx;
            head = head->next;
            prev_prev = prev;
            prev = curr;
        }

        if (mn == 1e9) {
            return vector<int>({-1, -1});
        } else {
            int mx = last_critical_idx - first_critical_idx;
            return vector<int>({mn, mx});
        }
    }
};
