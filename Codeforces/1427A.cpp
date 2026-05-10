#include <iostream>
#include <vector>
#include <algorithm>
 
int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> pos, neg;
        int pos_sum = 0, neg_sum = 0, zeros = 0;
        for (int i = 0; i < n; ++i) {
            int a_i;
            std::cin >> a_i;
            if (a_i == 0) {
                zeros += 1;
            } else if (a_i > 0) {
                pos_sum += a_i;
                pos.push_back(a_i);
            } else {
                neg_sum -= a_i;
                neg.push_back(a_i);
            }
        }
        
        if (pos_sum == neg_sum || zeros == n) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES" << std::endl;
            if (pos_sum > neg_sum) {
                for (int num : pos) std::cout << num << " ";
                for (int num : neg) std::cout << num << " ";
            } else {
                for (int num : neg) std::cout << num << " ";
                for (int num : pos) std::cout << num << " ";
            }
            while (zeros--) std::cout << "0 ";
            std::cout << std::endl;
        }
    }
}
