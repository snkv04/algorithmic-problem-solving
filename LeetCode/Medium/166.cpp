class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return std::string("0");

        long long num = static_cast<long long>(numerator);
        long long denom = static_cast<long long>(denominator);
        bool negative = false;
        if (num < 0) {
            negative = !negative;
            num *= -1;
        }
        if (denom < 0) {
            negative = !negative;
            denom *= -1;
        }

        long long wholes = num / denom;
        assert(wholes >= 0);
        num = num % denom;

        if (num == 0) {
            std::string result = negative ? "-" : "";
            result += to_string(wholes);
            return result;
        }

        vector<int> digits;
        int index_counter = 0;
        unordered_map<int, int> dividend_to_index;
        while (num * 10 < denom) {
            digits.push_back(0);
            ++index_counter;
            num *= 10;
        }

        while (
            num != 0 &&
            dividend_to_index.find(num) == dividend_to_index.end()
        ) {
            dividend_to_index[num] = index_counter++;
            num *= 10;
            int digit = num / denom;
            num %= denom;
            digits.push_back(digit);
        }

        std::string result = negative ? "-" : "";
        result = result + std::to_string(wholes) + ".";
        if (digits.size()) {
            if (num == 0) {
                for (const int &digit : digits)
                    result = result + std::to_string(digit);
                return result;
            } else {
                int first_in_cycle = dividend_to_index[num];
                for (int i = 0; i < first_in_cycle; ++i) {
                    result = result + std::to_string(digits[i]);
                }
                result = result + "(";
                for (int i = first_in_cycle; i < digits.size(); ++i) {
                    result = result + std::to_string(digits[i]);
                }
                result = result + ")";
                return result;
            }
        } else {
            result = result + "0";
            return result;
        }
    }
};
