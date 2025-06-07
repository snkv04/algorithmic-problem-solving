import java.util.*;
import java.io.*;

public class SubarraySums2 {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        long x = Long.parseLong(line[1]);
        long[] a = Arrays.stream(br.readLine().split(" ")).mapToLong(Long::parseLong).toArray();
        
        // first build the prefix sum array
        // remember that prefix[b]-prefix[a] gives the sum from (a, b]
        // so we can iterate through the prefix sum array, and for each one, we can simply see
        //// how many of the prefix sums strictly to the left (because subtracting two prefixes
        //// of the same element gives a subarray with no elements; nope) can be subtracted from
        //// the current prefix sum to obtain the target value x
        // and for seeing how many of the previous prefixes there are, we don't actually have
        //// to check all the prefixes to the left; we can set up a structure to denote how many
        //// prefixes there are of each specific value that we have found so far (a HashMap),
        //// and update it on each iteration (at each element)
        // also, in order to account for the fact that just the current prefix sum (the current
        //// element in the original array plus all the left elements) equals the target, we need
        //// to add to either add to the leftPrefixSums HashMap the element 0 with a frequency of 1
        //// or make a specific check for the current prefix equalling the target x; i chose
        //// the second one to keep the "leftPrefixSums" hashmap accurately named
        // genius
        long[] prefix = new long[n];
        prefix[0] = a[0];
        for (int i = 1; i <= n-1; i++) {
            prefix[i] = prefix[i-1] + a[i];
        }

        HashMap<Long, Long> leftPrefixSums = new HashMap<Long, Long>();
        long result = 0;
        for (int i = 0; i <= n-1; i++) {
            long currPreMinusX = prefix[i] - x;
            if (leftPrefixSums.containsKey(currPreMinusX)) result += leftPrefixSums.get(currPreMinusX);
            if (prefix[i] == x) result++;
            // adds the current prefix sum to the list (map) of ones covered
            if (leftPrefixSums.containsKey(prefix[i])) {
                leftPrefixSums.put(prefix[i], leftPrefixSums.get(prefix[i])+1);
            } else {
                leftPrefixSums.put(prefix[i], (long)1);
            }
        }
        pw.print(result);

        br.close(); pw.close();
    }
}
