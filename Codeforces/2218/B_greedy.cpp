#include <iostream>
#include <vector>
#include <algorithm>
 
int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::vector<int> pos, neg;
        for (int i = 0; i < 7; ++i) {
            int a_i;
            std::cin >> a_i;
            if (a_i >= 0) {
                pos.push_back(a_i);
            } else {
                neg.push_back(a_i);
            }
        }
        std::sort(pos.begin(), pos.end());
        std::sort(neg.begin(), neg.end());

        int sum = 0;
        if (neg.size() == 7) {
            for (int i = 0; i < 6; ++i) sum += -neg[i];
            sum += neg[6];
        } else if (pos.size() == 7) {
            for (int i = 0; i < 6; ++i) sum += -pos[i];
            sum += pos[6];
        } else {
            for (int i = 0; i < neg.size(); ++i) {
                sum += -neg[i];
            }
            for (int i = 0; i < pos.size(); ++i) {
                if (i < 6 - neg.size()) {
                    sum += -pos[i];
                } else {
                    sum += pos[i];
                }
            }
        }
        std::cout << sum << std::endl;
    }
}
