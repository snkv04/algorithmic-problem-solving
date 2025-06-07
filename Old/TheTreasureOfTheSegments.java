import java.util.*;
import java.io.*;

public class TheTreasureOfTheSegments {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            Integer[] l = new Integer[n];
            Integer[] r = new Integer[n];
            for (int i = 0; i<=n-1; i++) {
                String[] line = br.readLine().split(" ");
                l[i] = Integer.parseInt(line[0]);
                r[i] = Integer.parseInt(line[1]);
            }
            Integer[] lsorted = Arrays.copyOf(l, n);
            Integer[] rsorted = Arrays.copyOf(r, n);
            Arrays.sort(lsorted); Arrays.sort(rsorted);

            TreeMap<Integer, Integer> segmentsToRight = new TreeMap<>();
            segmentsToRight.put(lsorted[n-1], 1);
            for (int i = n-2; i>=0; i--) {
                int first = segmentsToRight.firstEntry().getValue();
                segmentsToRight.put(lsorted[i], first+1);
            }
            TreeMap<Integer, Integer> segmentsToLeft = new TreeMap<>();
            segmentsToLeft.put(rsorted[0], 1);
            for (int i = 1; i <= n-1; i++) {
                segmentsToLeft.put(rsorted[i], segmentsToLeft.lastEntry().getValue()+1);
            }

            int min = (int)3e5;
            for (int i = 0; i <= n-1; i++) {
                Integer numAfter = segmentsToRight.ceilingKey(r[i]+1);
                Integer numBefore = segmentsToLeft.floorKey(l[i]-1);
                min = Math.min(min, (numAfter!=null?segmentsToRight.get(numAfter):0)
                    + (numBefore!=null ? segmentsToLeft.get(numBefore):0));
            }
            pw.println(min);
        }

        br.close(); pw.close();

        // how to check if two segments intersect? consider two segments that do not intersect.
        // the right end of the segment to the left must be STRICTLY to the left of the left
        // end of the right segment. if these two values are equal, then the two segments will
        // be considered intersecting.
        // the most intuitive, but way too slow, solution is obviously to just go through
        // each segment and count the number of other segments it intersects, and the answer
        // would be the maximum of this value across all segments (or the minimum, across all
        // segments, of how many segments are not intersected by each segment). this solution
        // is O(n^2), which obviously won't pass.
        // it would be nice if for each point on the number line, we could see how many segments
        // are non-intersecting to that point, either strictly to the right or strictly to the
        // left of that point. that way, we actually could iterate over all segments and calculate
        // how many segments it does not intersect in O(1), making this checking part of the
        // solution just O(n), by checking the number of segments with their left end strictly
        // to the right of the current segment plus the number of segments with their right end
        // strictly to the left of the current segment. this could be done with prefix and suffix
        // sums, where the value at any point would say the number of segments to the left/right
        // of it.
        // however, we can't make a prefix sum or suffix sum array of size 10^9, which is the
        // range of possible values for the segment ends, because this would be too big. so,
        // instead, we can "skip" from point to point of interest. first, we can make a TreeMap
        // that maps a point to how many FULL SEGMENTS are to the right of that point or on it
        // (i.e. how many segments have their left end on or to the right of the point). for
        // example, if there is a segment with its left end on 4, one with its left on 5, another
        // with its left on 5, and one with its left on 6 (where all of the right ends are
        // arbitrary and do not matter because for each segment, l<=r), then the point 6 has 1
        // full segment that "ends" on or to the right of it, the point 5 has 3, and the point
        // 4 has 4. with something like this, if we are looking at another specific segment and
        // we want to know how many segments it doesn't intersect to its right, then if its right
        // bound is r, then we can simply get the mapped value of ceil(r+1), as that would be
        // the closest point strictly to its right and see how many segments there are on that
        // side. (if we do ceil(r), then we run the risk of intersecting segments being counted
        // as nonintersecting). if there aren't any (i.e. if ceiling returns null), then there
        // are 0 to that side. to set up this treemap, we can sort all of the segments' left
        // bounds, and then make somewhat of a suffix sum map (instead of an array which looks
        // at every point on the number line) for how many are on or to the right of that point.
        // when iterating over each segment for our final check, we can see how many are STRICTLY
        // to the right of that segment's right bound. we can basically do this logic but flipped
        // for the other end, so that when checking how many total segments a segment doesn't
        // intersect, we just do numToLeft + numToRight.
        // also, one potential issue when constructing the map is if two segments have the same
        // right (or left) bound. we can deal with this by replacing the entry in the map with
        // another entry that has the same key but an incremented value. for example, consider
        // a segment with its right end on 1, a segment with its right on 2, one with its right
        // on 3, and another with its right on 3. the map will be constructed left to right.
        // since all previous values (points/segment ends) are less than or equal to the current
        // one, we can just take the last entry in the treemap, take its value, and use that+1
        // for the new entry. if the new entry has the same point, such as going from (3 segments
        // fully to the left or on 3) to (4 segments fully to the left or on 3), then the last
        // element gets replaced when doing put(3, lastEntry.getValue+1).
        // when considering time complexity, we first need to sort the two lists of segment bounds,
        // which is O(nlogn). then we construct the treemaps, which i think should be O(nlogn),
        // but each element's point is greater than the max point in the treemap (or reverse for
        // the other map), so maybe it's just O(n). then, for checking each segment and how many
        // it doesn't intersect, the treemap does a O(logn) search for both the ceiling and floor
        // functions, meaning this will in total take O(nlogn). as such, the total time complexity
        // for this solution is O(nlogn).
    }

    // // // //

    static class Multiset {
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }
}
