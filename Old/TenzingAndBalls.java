import java.util.*;
import java.io.*;

public class TenzingAndBalls {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // int t = Integer.parseInt(br.readLine());
        // for (int i = 1; i <= t; i++) {
        //     int n = Integer.parseInt(br.readLine());
        //     int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        //     TreeSet<Integer>[] indexList = new TreeSet[n+1];
        //     for (int j=1;j<=n;j++) {
        //         indexList[j]=new TreeSet<Integer>();
        //     }
        //     TreeSet<Integer> workingIndices = new TreeSet();
        //     for (int j = 0;j<=n-1;j++) {
        //         indexList[a[j]].add(j); // adds the index to that color's index list
        //         workingIndices.add(j);
        //     }

        //     int ans = 0;
        //     for (int color = 1; color<=n; color++) {
        //         if (indexList[color].isEmpty() || indexList[color].size() == 1) continue;

        //         int maxIndex = indexList[color].last();
        //         int minIndex = indexList[color].first();
        //         Integer j = minIndex;
        //         while (j != null && j <= maxIndex) {
        //             // if (workingIndices.contains(j)) {
        //                 workingIndices.remove(j);
        //                 indexList[a[j]].remove(j);
        //             // }
        //             ans++;
        //             j = workingIndices.higher(j);
        //         }
        //     }
        //     pw.println(ans);
        // }

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            // memo[i] represents the max removeable after doing remove operations from indices 1 to i
            int[] memo = new int[n+1];
            int[] maxPerColor = new int[n+1];
            for (int color=0; color<=n; color++) maxPerColor[color] = -1000000000;
            for (int j = 1; j <= n; j++) {
                memo[j] = Math.max(memo[j], memo[j-1]);
                memo[j] = Math.max(memo[j], maxPerColor[a[j-1]] + j);
                maxPerColor[a[j-1]] = Math.max(maxPerColor[a[j-1]], memo[j-1]-(j-1));
                // pw.println("on element j="+j+", and memo="+Arrays.toString(memo)+" and maxpercolor="+Arrays.toString(maxPerColor));
                // here, maxPerColor[color] denotes the maximum number of balls that
                // can be removed across a subarray that ends with that color, out of
                // all subarrays starting at 1 and ending at that color
                
                // for (int k = 1; k <= j-1; k++) {
                //     if (a[j-1]==a[k-1]) {
                //         memo[j] = Math.max(memo[j], memo[k-1]+j-k+1);
                //     }
                // }
                // memo[j] = Math.max(memo[j], memo[j-1]);
            }
            pw.println(memo[n]);
        }

        br.close(); pw.close();

        // first of all, we know that every segment of elements that we remove
        // has to be pairwise disjoint from all the others. this is because if there
        // are two "interlocking" segments, then once one is removed, then the endpoint
        // of the other is also gone and we can't remove it (and may instead have to
        // find another element outside of the deleted segment with the same color as
        // the endpoint). now, using dynamic programming, denote memo[i] to be equal to
        // the maximum number of elements that can be removed if we remove these disjoint
        // segments anywhere from indices 1 to i of the original array. for each element
        // index i (or j in the code because i is reserved for the test cases lol), we
        // can either choose to cut off a segment ending at i or simply not do anything.
        // obviously, if we don't do anything, memo[i] will be equal to memo[i-1] since
        // no new balls have been removed since the previous element. if we do actually
        // remove a segment ending at j, then we have to look at all previous elements
        // with the same color as j, and whichever has the maximum value of memo, we
        // can cut out a segment that starts at that element and ends at the current index
        // (since they will have the same color); this is mathematically represented
        // as memo[previousElementIndex] + j-previousElementIndex+1, since the second
        // part is the length of the segment being removed and the first part is the
        // max number of balls removed at the element right before the beginning of the
        // segment currently being cut out. for each memo[j], we take the max of these
        // two values. if we call the current index j, there can be several elements
        // before element j one which all have the same color as element j, and out of
        // them we want the element at index k such that memo[k] is higher than
        // the memoized result of all the other elements with the same color before j.
        // however, in our main pass from 1 to n, for each one we have to look through
        // all the previous elements to find the aforementioned max memo element. so,
        // to reduce this from O(n^2) to just O(n), we can keep that result stored for
        // each color. if we cut out a segment, then the new memoized result for the
        // current index j will be memo[k-1] + j-(k-1), right? the memo[k-1]-k+1 can
        // simply be stored for each color, so that when we find a new current element
        // (in the main pass through the indices) with the same color as the stored value,
        // we can literally just add j to it (index of end of to-be-removed segment)
        // and the rest of the expression is substituted by the stored value so that
        // it is accurate. then we can compare this with not removing anything. to
        // actually store it, we can do it WHILE going through the array; since we
        // know that we're ending the segment at a later index, the start of the segment
        // for the color in question is just the current index. this continues to be
        // optimized for the same color later on. so, the stored value of memo[k-1]-k+1
        // is just going to be memo[j-1]-j+1 while going through the array.
        // to briefly explain the code, first we set up a memo array and then an array
        // that tells us, for each color, what is the maximum number of elements that
        // we can remove if the last segment removed ends on that color, MINUS the index
        // of the end of that segment minus 1. while going through, we make the memoized
        // result of the current element j equal to the max of the following two options:
        // we don't do anything (making the removed elements the same value as that of
        // the previous index), or we remove a segment that ends on the current index
        // and begins on an index to the left such that the ball at that index is the
        // same color and that starting the segment at this specific ball maximizes
        // the result for the current index j. then we make the maximum value of this
        // color equal to the memoized result of the previous element minus the current
        // index+1, setting up this color to be fully optimized if a segment STARTS at
        // it in the future.
        // math. goddamn, this was (although simple) such a hard problem.
    }
}
