import java.util.*;
import java.io.*;

public class PermutationPartitions {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int k = sc.nextInt();
        HashSet<Integer> maxes = new HashSet();
        long partitionValue = 0;
        for (int i = 0; i <= k-1; i++) { maxes.add(n-i); partitionValue += n-i; }

        TreeSet<Integer> indices = new TreeSet(); // holds indices of max values
        for (int i = 1; i <= n; i++) {
            int element = sc.nextInt();
            if (maxes.contains(element)) {
                maxes.remove(element);
                indices.add(i);
            }
        }

        long numPartitions = 1;
        int mod = 998244353;
        while (indices.size() > 1) {
            int first = indices.first();
            int second = indices.higher(indices.first());
            numPartitions *= second - first;
            numPartitions %= mod;
            indices.pollFirst();
        }
        pw.print(partitionValue + " " + numPartitions);

        sc.close(); pw.close();

        // we have k segments in the partition, so preferably each segment has the max
        // value available (where a value is "available" if another segment hasn't taken it).
        // so, these maximum values that are spread out across the segments would be the
        // k values ranging from n to n-k+1. for example, if n (the length of the array)
        // is 10 and k (the number of segments) is 4, then the values 10, 9, 8, and 7
        // should each be in one segment. we now want to count the number of different
        // partitions that have segments like this. consider two adjacent segments (or,
        // rather, the max values in them) and assume there are x non-max elements between
        // them. without considering any of the other segments and only looking at these
        // two max values, either the first segment can contain none of the x values and
        // the second one has all of them, the first segment has its max and the leftmost
        // non-max value while the second one has the rest, the first segment has its max
        // and the two leftmost non-max values while the second one has the rest, ...,
        // or the first segment has its max value and all of the non-max values while the
        // second segment only has its max value. this means that there are x total choices
        // for this gap between the two max values. by the multiplication principle of
        // combinatorics/counting, we just multiply the number of choices for each of
        // these gaps together, since for each choice of a selected gap, the other gaps
        // can do all of their variations, so we end up with the total number of partitions
        // with maximum partition value being the product of the lengths of all the gaps.
        // this can easily be found by sorting the positions of the indices of all the
        // max values. by the way, if the last few or first few elements of the permutation
        // are not any of the maxes (i.e. don't have a left-side max if they're at the
        // beginning or a right-side max if at the end), then the only choice for which
        // segment they are part of is simply being part of the first (or last if at end)
        // segment. also, the actual max partition value is simply the sum of the k max
        // values, since each of them are in one segment and, because of this, the segments
        // have been optimized.
    }
}
