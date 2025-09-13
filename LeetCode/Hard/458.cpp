class Solution {
private:
    int pow(int base, int exp) {
        if (exp == 0) return 1;

        int result = pow(base, exp / 2);
        result *= result;
        if (exp % 2) result *= base;
        return result;
    }

public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        /*
        - for some given number of buckets, how many pigs do you need to
        test all of them if you can only test once? well, let's flip the
        problem around. suppose you have N pigs; how many buckets can you
        test in one test? well, we want each bucket to have a unique set
        of pigs assigned to it. from there, we can see that we can assign
        a bucket to each unique subset of pigs, so we can check around 2^N
        buckets. i say "around" because there might be some edge cases in
        terms of handling the empty subset case.
        - now, note that based on minutesToDie and minutesToTest, we can
        easily find the total number of tests we can perform.
        - let's expand the idea mentioned above to performing more than
        one test.
            - let's first talk about a new way of thinking about binary
            representations.
                - consider a cube with its 8 octants. if we
                number each one from 0-7 in row-major order, then we can
                uniquely identify a cell based on its binary representation
                as follows: the first bit will say the row (first or second),
                the second bit will say the column, and the third bit will
                say which half in the depth dimension the cell is in.
                - imagine there are 5 dimensions. numbers from 0 to 2^5-1 each
                represent a unique location in the 5-dimensional space, where
                there are two possible locations (halves) in each dimension.
                for example, the number 11001 (25) says right, right, left,
                left, right, where each word is one of the halves among each
                dimension.
                - put simply, the base is the number of possible cells among
                each dimension, and the exponent is the number of dimensions.
                given that simple framework, each number from 1 to base^exp
                has a unique location that can be denoted with a single number
                from the base-b number system, where exp is the number of
                digits in that number.
            - how is that method of thinking about binary representations
            useful here?
                - well, consider only running a single test. with N pigs,
                we can uniquely identify which bucket is poisonous among
                2^N buckets. the first pig will be the most significant bit;
                it will be used on the first 2^(N-1) buckets. the second pig
                will be the second most significant bit, and it will be used
                on the first set of 2^(N-2) buckets and the third set (there
                are 4 total sets of that size). and so on.
                - in a single-test scenario, what actually dictates which
                whether a specific bit of the poisoned bucket is turned on
                or off? well, it's just whether the pig for that bit died
                or not.
            - now, let's expand it to multiple tests.
                - if we have 2 tests, for example, each pig will either die
                in the first test, in the second test, or never. so, instead
                of having each pig cut the search space in half (like if there
                are N buckets, then we have the most significant digit pig test
                the first N/2 and not the second N/2), we can instead have each
                pig cut the search space in third (in the first test, we test
                the most significant digit pig on the first N/3 buckets, in the
                second test we test it on the second N/3 buckets, and if it
                doesn't die in either of those then the poisoned bucket is in
                the last N/3 buckets).
                - so, the number of tests directly empowers each pig to be
                used to extract more information. specifically, the "more
                information" means a higher base in terms of the base-b
                representation of the bucket that is poisoned.
                - the final answer is just the lowest number of bits that we
                need to encode all possible buckets.
        - why can't we use tests as the exponent and the number of pigs as
        the base? why does that not make sense contextually?
            - first off, we can't do the +1 thing on any of the dimensions.
            if we assume the base to be pig count P and the number of digits
            to be T+1, then since one of the digits isn't covered by any of the
            tests, we are simply not gathering information about where the
            bucket is ACROSS A WHOLE DIMENSION. if we assume the base to be
            P+1 and the digit count to be T, then for each dimension, we have
            a segment from that dimension that we are just not testing because
            we don't have any pigs to cover that segment of that dimension. so,
            let's say we are using a base P and T digits.
            - if there are 8 buckets, assuming we have 3 tests and 2 pigs, what
            would the poisoned bucket being 5 (101) mean? for the first test,
            we are putting one pig on buckets 0,1,2,3 and another pig on buckets
            4,5,6,7. for the second test, we are putting one pig on 0,1,4,5
            and another pig on 2,3,6,7. let's stop right there. if a pig dies
            in an earlier test, then it already can't be used for a later test.
            in the other case, where we swap how pigs and tests are used
            (between being used for the base and the exponent), it doesn't
            matter if the pig died on an earlier test, because if it dies, we
            immediately will have gotten the information we need out of it 
            (namely, what the value of its digit is). in this current case,
            if a pig dies, then we can't narrow down the search space to any
            greater granularity in subsequent tests.
            - more generally, if a fixed bit iterates through its possible
            values and stops at some point, that was still useful because it
            can be set to the value it stopped at. however, if we iterate
            from 0 to the number of bits - 1 for each possible value that a bit
            can take on, then that means that each possible value can only
            be assigned to one of the bits, and we'll need a new pig to find
            the correct segment for each additional layer of granularity
            (i.e., the correct value for each bit).
            - so, the thing that is fixed is the base (meaning that the
            number of tests will tell us how many segments we can distinguish
            between at each level of granularity, or how many splits we can
            separate each dimension into), and we just have to find the
            exponent (i.e., the number of pigs).
        */
        int tests = minutesToTest / minutesToDie, pigs = 0;
        while (pow(tests + 1, pigs) < buckets) {
            ++pigs;
        }
        return pigs;
    }
};
