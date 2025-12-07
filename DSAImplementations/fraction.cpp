#include <bits/stdc++.h>

long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    long long max_op = std::max(a, b), min_op = std::min(a, b);
    while (min_op != 0) {
        long long rem = max_op % min_op;
        max_op = min_op;
        min_op = rem;
    }
    return max_op;
}

long long lcm(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

struct Frac {
    Frac(long long n, long long d) : num(n), denom(d) {
        reduce();
    }

    Frac(long long x) : num(x), denom(1) {}

    bool operator<(const Frac &other) const {
        long long new_denom = lcm(denom, other.denom);
        long long num1 = num * (new_denom / denom), num2 = other.num * (new_denom / other.denom);
        return num1 < num2;
    }

    bool operator==(const Frac &other) const {
        Frac frac1 = *this, frac2 = other;
        frac1.reduce(); frac2.reduce();
        return frac1.num == frac2.num && frac1.denom == frac2.denom;
    }

    bool operator!=(const Frac &other) const {
        return !(operator==(other));
    }

    bool operator<=(const Frac &other) const {
        return operator<(other) || operator==(other);
    }

    void reduce() {
        long long g = gcd(num, denom);
        num /= g;
        denom /= g;
        if (denom < 0) {
            num = -num;
            denom = -denom;
        }
    }

    Frac operator+(const Frac &other) {
        long long new_denom = lcm(denom, other.denom);
        long long num1 = num * (new_denom / denom), num2 = other.num * (new_denom / other.denom);
        Frac result(num1 + num2, new_denom);
        result.reduce();
        return result;
    }

    Frac operator-(const Frac &other) {
        return operator+(Frac(-1) * other);
    }

    Frac operator*(const Frac &other) {
        Frac result(num * other.num, denom * other.denom);
        result.reduce();
        return result;
    }

    Frac operator/(const Frac &other) {
        return operator*({other.denom, other.num});
    }

    long long sign() {
        reduce();
        if (num == 0) return 0;
        else if (num > 0) return 1;
        else return -1;
    }

    friend std::ostream& operator<<(std::ostream &os, const Frac &fraction) {
        os << fraction.num << "/" << fraction.denom;
        return os;
    }

    long double to_ld() {
        assert(denom != 0);
        return static_cast<long double>(num) / static_cast<long double>(denom);
    }

private:
    long long num, denom;
};
