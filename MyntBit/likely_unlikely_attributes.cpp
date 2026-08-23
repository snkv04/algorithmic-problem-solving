#include <vector>
#include <unordered_set>

class OrderValidator {
private:
    std::unordered_set<int> valid_symbols;

public:
    // Constructor initializes the allowed symbols
    OrderValidator(const std::vector<double>& allowed) {
        for (double s : allowed) {
            valid_symbols.insert(static_cast<int>(s));
        }
    }

    bool validate(double price, double quantity, int symbol_id, int side) {
        if (
            price > 0 &&
            quantity > 0 &&
            valid_symbols.count(symbol_id) &&
            (side == 1 || side == 2)
        ) [[likely]] {
            return true;
        } else [[unlikely]] {
            return false;
        }
    }
};
