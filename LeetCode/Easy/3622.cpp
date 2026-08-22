class Solution {
public:
    bool checkDivisibility(int n) {
        int digit_sum = 0, digit_product = 1, copy = n;
        while (copy) {
            int digit = copy % 10;
            copy /= 10;
            digit_sum += digit;
            digit_product *= digit;
        }
        return n % (digit_sum + digit_product) == 0;
    }
};
