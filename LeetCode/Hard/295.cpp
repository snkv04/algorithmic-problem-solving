struct Comp {
    bool operator()(const int &a, const int &b) {
        return a > b;
    }
};

class MedianFinder {
private:
    priority_queue<int> lower_half;
    priority_queue<int, vector<int>, Comp> upper_half;

public:
    MedianFinder() {
        // do nothing
    }

    // if uneven, prefer extra element on lower half
    void balance() {
        if (lower_half.size() < upper_half.size()) {
            int moving = upper_half.top();
            upper_half.pop();
            lower_half.push(moving);
        }

        if (lower_half.size() > upper_half.size() + 1) {
            int moving = lower_half.top();
            lower_half.pop();
            upper_half.push(moving);
        }
    }
    
    void addNum(int num) {
        if (lower_half.empty()) {
            lower_half.push(num);
        } else {
            if (num > lower_half.top()) {
                upper_half.push(num);
            } else {
                lower_half.push(num);
            }
        }

        balance();
    }
    
    double findMedian() {
        if (lower_half.size() > upper_half.size()) {
            return (double) lower_half.top();
        } else {
            return (double) (lower_half.top() + upper_half.top()) / 2;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
