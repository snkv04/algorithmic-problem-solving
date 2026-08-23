class FieldLogger {
    int count_ = 0;
    double sum_ = 0.0;
public:
    template<typename... Ts>
    void log(Ts... values) {
        // Counts the number of parameterss in the
        // template parameter pack
        count_ += sizeof...(Ts);

        // Uses a fold expression to sum up the whole
        // set of arguments
        sum_ += (... + static_cast<double>(values));
    }

    int count() const { return count_; }
    double sum() const { return sum_; }
};
