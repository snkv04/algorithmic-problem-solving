#include <vector>
#include <map>
#include <list>
#include <unordered_map>
#include <utility>

class LimitOrderBook {
private:
    struct Order {
        int id;
        double price;
        double qty;
    };

    std::map<double, std::list<Order>> by_price;
    std::unordered_map<int, std::list<Order>::iterator> iterators;

public:
    LimitOrderBook() {}

    void add_order(int id, double price, double qty) {
        // pushes the order
        Order order{id, price, qty};
        by_price[price].push_back(order);

        // maintains an iterator to where it is in
        // the list
        auto it = by_price[price].end();
        --it;
        iterators[id] = it;
    }

    bool cancel_order(int id) {
        if (iterators.count(id)) {
            // removes from iterators map
            auto it = iterators[id];
            iterators.erase(id);

            // removes from prices map
            double price = it->price;
            by_price[price].erase(it);
            if (by_price[price].empty()) {
                by_price.erase(price);
            }

            // operation was valid
            return true;
        } else {
            return 0;
        }
    }

    double get_best_price() {
        if (by_price.empty()) {
            return -1;
        } else {
            return by_price.rbegin()->first;
        }
    }

    double execute_market_sell(double qty) {
        double matched = 0.0;
        while (qty && by_price.size()) {
            int id = by_price.rbegin()->second.begin()->id;
            auto it = iterators[id];
            Order& order = *it;
            if (order.qty > qty) {
                matched += order.price * qty;
                order.qty -= qty;
                qty = 0;
            } else {
                qty -= order.qty;
                matched += order.price * order.qty;
                cancel_order(id);
            }
        }
        return matched;
    }
};
