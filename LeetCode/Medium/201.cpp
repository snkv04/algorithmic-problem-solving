class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int ans = 0;
        for (int i = 0; i < 31; ++i) {
            int exp = 1 << i;
            if ((left & exp) && (right & exp) && (right-left+1<=exp)) {
                ans += exp;
            }
        }
        return ans;
    }
};
