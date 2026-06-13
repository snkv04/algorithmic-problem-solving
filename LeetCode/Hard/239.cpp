class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // basic idea: we want a decreasing monotonic stack, where the
        // top element is the back (right) of the deque, but then at each
        // index, we care about the bottom of the stack (the max element)

        // initializes the deque before the first full window
        deque<int> d;
        auto push = [&](int idx) {
            // removes the bottom of the stack if it's too far left
            // of the current index
            if (d.size() && d.front() == idx - k)
                d.pop_front();

            // enforces the monotonic stack property of being strictly
            // (though maybe strictness is not important here) decreasing
            while (d.size() && nums[d.back()] <= nums[idx])
                d.pop_back();

            // pushes the current index onto the stack
            d.push_back(idx);
        };
        for (int i = 0; i < k - 1; ++i) push(i);

        // iterates through each window, and for each, gets the bottom
        // of the stack
        vector<int> ans;
        for (int i = k - 1; i < nums.size(); ++i) {
            push(i);
            ans.push_back(nums[d.front()]);
        }
        return ans;
    }
};
