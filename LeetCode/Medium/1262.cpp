class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int sum = 0, one1 = 1e9, one2 = 1e9, two1 = 1e9, two2 = 1e9;
        for (int num : nums) {
            sum += num;
            if (num % 3 == 1) {
                if (num < one1) {
                    one2 = one1;
                    one1 = num;
                } else if (num < one2) {
                    one2 = num;
                }
            } else if (num % 3 == 2) {
                if (num < two1) {
                    two2 = two1;
                    two1 = num;
                } else if (num < two2) {
                    two2 = num;
                }
            }
        }

        if (sum % 3 == 0) {
            return sum;
        } else if (sum % 3 == 1) {
            int best = 0;
            if (one1 != 1e9) best = max(best, sum - one1);
            if (two2 != 1e9) best = max(best, sum - two1 - two2);
            return best;
        } else {
            int best = 0;
            if (two1 != 1e9) best = max(best, sum - two1);
            if (one2 != 1e9) best = max(best, sum - one1 - one2);
            return best;
        }
    }
};
