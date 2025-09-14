/*
i=0, subtracting -1 (adding 1)
i=1, subtracting 0
i=2, subtracting 2
i=3, subtracting 6
i=4, subtracting 14
*/

class Solution {
private:
    int countBits(long long num) {
        int bits = 0;
        while (num) {
            bits += num % 2;
            num = (num >> 1);
        }
        return bits;
    }

public:
    int makeTheIntegerZero(int num1, int num2) {
        if (num2 >= num1) return -1;

        for (long long numOps = 1; numOps <= 60; ++numOps) {
            long long newNum = num1 - numOps * num2;
            if (newNum <= 0) break;
            if (newNum < numOps) continue;

            if (countBits(newNum) <= numOps) {
                return numOps;
            }
        }
        return -1;
    }
};
