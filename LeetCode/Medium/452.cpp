class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        /*
        generalizable ideas:
        - why sort by endpoint instead of by startpoint? well, both work.
            - if we sort by the endpoint, and then go from least to greatest
            endpoint, then we know that for a given interval, all future ones
            will end after (or equal to) its end. so, for the current interval,
            we can always greedily shoot an arrow at its end to capture as many
            future intervals as possible. once a future interval has its start
            be strictly greater than the current interval's end, then we know
            that we strictly cannot use the same arrow for both, so then we
            set that future one to the current and then try to again merge it
            with as many future ones as possible until we can't.
            - if we sort by the startpoint, and then go from least to greatest
            startpoint, then we know that for a given interval, all future ones
            will start after (or equal to) its end. so, for the current
            interval, we have to keep track of the earliest endpoint across all
            of the ones that we merge it with, because we know that the
            "intersection" segment representing the intersection of all the
            segments we're merging it with will continuously have its left side
            move more and more right, but the right side might move right or
            left (consider the intervals [1, 4] and [2, 3]). so, since we are
            passing through the intervals from left to right again, we want to
            shoot the arrow at the rightmost point, but we need to keep track of
            how far right we can shoot while still hitting all of the intervals
            merging with the current interval, and then eventually we'll see an
            interval that doesn't overlap with all of them and we strictly need
            a new arrow.
            - i think in general, the sorting by right end is more intuitive,
            since we sort by right end and want each arrow to go as far to the
            right as possible. however, the other method is probably also good
            to know. what's at the core of that other method? we sort by the
            left endpoint (i.e., startpoint), but since we are going left to
            right (and therefore we want to shoot our arrows as far right as
            possible), we keep track of how far right we can shoot while
            processing each interval. this effectively "merges" a series of
            intervals (which are contiguous when sorted by left side) together
            until the next one does not fit onto the merged interval. in short:
            sort by left side, merge intervals together by keeping track of
            the leftmost right side, start a new "merged" interval when the
            left side doesn't overlap with the last merged interval.
        - oftentimes, in other problems, we "jump" between the endpoints of
        the intervals in sorted order, so we don't always process both sides
        of an interval before processing a side of another interval. however,
        in this problem, we are processing full intervals based on their right
        side. in other words, we are basically jumping between the intervals'
        right sides. put simply, the question is, how do we know that we have
        to do this? i guess, just try both (of iterating through endpoints and
        iterating through the intervals themselves). in this case, iterating
        through the intervals works very well, since the idea of "shooting an
        arrow at the rightmost point for each interval to capture as many
        future intervals as possible" is easy to implement when iterating
        through the intervals based on their right side.
        */

        sort(
            points.begin(),
            points.end(),
            [](const vector<int> &a, const vector<int> &b) {
                return a[1] < b[1];
            }
        );

        int ans = 1;
        vector<int> &curr = points[0];
        for (int i = 1; i < points.size(); ++i) {
            if (points[i][0] > curr[1]) {
                curr = points[i];
                ++ans;
            }
        }
        return ans;
    }
};
