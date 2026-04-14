class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        /*
        - problem:
            - we have B buckets of liquid. we want to identify which bucket
            is poisonous.
            - what we are able to do is, in a single test, assign pigs to
            buckets (where a bucket can have multiple pigs and a pig can
            drink from multiple buckets), and make all pigs drink their buckets.
            a pig will either die or live.
            - we have a fixed number of tests. how many pigs do we need?
        - solution:
            - since we have T tests, we can use a single pig to distinguish
            between T+1 groups of buckets. how? for simplicity, let B = (T+1)^K
            for some K. then, in the first test, let the pig drink from the
            first B/(T+1) buckets. in the second test, it drinks from buckets
            in [B/(T+1) + 1, 2B/(T+1)]. and on and on. if it never dies, then
            the poisonous bucket is in the last B/(T+1) buckets. if it does,
            then we know which group it was from.
            - we can do this with all the pigs, and combine their "which group
            is the poisonous bucket in" information by placing each bucket
            into a distinct combination of groups. this combination can be
            written as a string, or a number in base (T+1).
            - therefore, we can treat each bucket as having a non-negative
            index, written in base (T+1). each pig corresponds to a digit,
            and through conducting the T tests, a single pig will tell us
            what value the poisonous bucket has on that digit. the digits
            altogether will tell us the index of the poisonous bucket.
            - then, we simply need to find how many digits we need to represent
            every bucket. that's just straightforwardly equal to the minimum
            possible K such that (T+1)^K >= B.
        - notes:
            - if we only have one test, then a single pig will either die or
            not die. if we have T tests, then a single pig will either die in
            the first, the second, ..., the T'th test, or not at all. as a
            result, each pig can be used to distinguish between (T+1) groups
            of buckets.
            - then, the question of how many pigs we need is the question of
            how many different ways do we need to split the buckets into (T+1)
            groups so that every bucket has a unique combination of pig death
            times
                - in general, that's also how i should view the binary
                representation of a number; each bit will distinguish between
                two different GROUPS of numbers, and the question of "how many
                bits are needed" refers to "how many different ways do we need
                to split the numbers into exactly 2 groups so that each number
                has a unique combination of groups"
            - "a bucket can have multiple pigs" just means that we can have
            more than one digit for each bucket/number. "a pig can have
            multiple buckets" means that all buckets sharing the same value
            for a particular digit can be tested at once, in a single test with
            a single pig.
        - useful ideas for the future:
            - the maximum information that we can get out of a pig ISN'T which
            of T+1 buckets has the poison. it's which of T+1 GROUPS of buckets
            has the poison. more generally, when trying to identify some number
            or object, the maximum information that a single digit can give us
            is tell us which of B groups of objects it's in, where the number
            is in base B.
            - it's a simpler thought process to think of "for a fixed number
            of tests, how many buckets can we distinguish between with a single
            pig, and for each new pig" than "for a fixed number of pigs, how
            many buckets can we distinguish between with a single test, and
            for each new test". the general form, where we have a nontrivial
            number of tests and pigs, is easier to arrive at from the first
            thought process. how to always go through the simpler thought
            process? you can't know it beforehand. so, use Polya's mouse.
            - instead of "for a fixed bucket number, what's the minimum number
            of pigs we need", we think about the problem as "for a fixed
            number of pigs, the distinguishable buckets are fixed. what's the
            minimum number of pigs we need so that the distinguishable buckets
            is greater than (or equal to) the given buckets?". in simpler
            terms, the idea is that the number of buckets we can identify
            is monotonically increasing with the number of pigs we use.
        */

        int tests = minutesToTest / minutesToDie;
        int can_identify = 1;  // # of buckets we can uniquely identify
        int pigs = 0;
        while (can_identify < buckets) {
            ++pigs;
            can_identify *= (tests + 1);
        }
        return pigs;
    }
};
