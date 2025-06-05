import java.util.*;
import java.io.*;

public class BerryPicking {
    static int n, k;
    static int[] b;
    // static int bucketSize;

    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("berries.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("berries.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        k = Integer.parseInt(line[1]);
        b = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(b);
        int minElsie = b[n-1];
        int max = 0;
        for (int i = 1; i <= minElsie; i++) {
            max = Math.max(max, solve(i));
        }
        pw.println(max);

        br.close(); pw.close();

        // we want to find the maximum amount of berries bessie can have, given that
        // all of bessie's baskets have less than or equal to elsie's baskets. in other
        // words, there is a threshold where every basket of elsie's is greater than or
        // equal to it and every basket of bessie's is less than or equal to it. notice that
        // elsie should never have any number strictly greater than the threshold and should
        // instead have all of her baskets exactly on the threshold, as otherwise she would
        // potentially be taking away berries from trees that bessie should have since she's
        // the one whose berries we are trying to maximize. we can complete search every
        // threshold (range of elsie's min bucket size = [1, max berries on any tree]),
        // as it can't be binary searched since the function "max_berries(threshold)"
        // may have various peaks, i.e. may increase then decrease and is not monotonic (i
        // think). so, for each threshold, we go through all of the trees and take out
        // threshold-sized chunks until all of elsie's buckets are filled. if there aren't
        // enough trees with threshold-sized chunks to fill all of elsie's buckets, then
        // this threshold simply won't work, since filling up her remaining buckets with
        // less than the threshold means that those buckets may instead become bessie's,
        // and the ordering and splitting of bucket sizes then becomes messy. so, after
        // filling up all of elsie's buckets, we then fill up bessie's buckets. we want
        // to maximize the total sum, so we start off by trying to fill up threshold-sized
        // buckets. once no tree at all contains any more of these-sized chunks (i.e. all
        // of the trees have less than or equal to the threshold), then we resort the trees
        // by the remaining berries and get as many for bessie as we can. we then return
        // the number of berries bessie gets. the answer is the max of this value across
        // all attempted threshold values.
        // basically, we know the top k/2 buckets go to elsie and the bottom go to bessie.
        // this means that elsie's minimum bucket is >= bessie's maximum bucket. we don't
        // know what bucket size maximizes bessie's output, so we brute force it. elsie's
        // minimum bucket size can go from 1 all the way to the maximum number of berries
        // on any tree. to maximize bessie's output, we can minimize elsie's output and
        // make every bucket only have {threshold} berries. if all the trees don't have
        // enough berries to collectively hold k/2 discrete sets of berries of size {threshold},
        // then that threshold obviously doesn't work. so we fill up all of elsie's buckets.
        // then, we want to maximize bessie's buckets, so we get as many as we can of size
        // {threshold}. unfortunately, it may not be the case that all of them can be this
        // size, but we still want to optimize them. after all the trees have remaining
        // amounts less than {threshold}, sort them and keep filling up bessie's buckets
        // until either they all are done or there are no more berries on the trees left.
        // do this for each threshold value (minimum size of elsie's buckets), and find
        // the maximum output bessie can get across all of them.
    }

    static int solve(int minElsie) {
        int[] berries = Arrays.copyOf(b, b.length);
        int bucketsE = k/2, bucketsB = k/2;
        int i = n-1;
        while (bucketsE > 0 && i>=0) {
            if (berries[i] < minElsie) return 0;

            int numBuckets = Math.min(bucketsE, berries[i]/minElsie);
            bucketsE -= numBuckets;
            berries[i] -= numBuckets * minElsie;
            if (bucketsE > 0 || (bucketsE == 0 && berries[i]<minElsie)) {
                i--;
            }
        }
        if (bucketsE > 0) return 0; // went through all trees and elsie not done

        int sumB = 0;
        while (bucketsB > 0 && i>=0) {
            if (berries[i] < minElsie) break;

            int numBuckets = Math.min(bucketsB, berries[i]/minElsie);
            berries[i] -= numBuckets * minElsie;
            sumB += numBuckets * minElsie;
            bucketsB -= numBuckets;
            i--;
        }

        if (bucketsB > 0) {
            // bucketSize = minElsie;
            Arrays.sort(berries); // only the remainders after taking out all the minElsie sized chunks
            i = n-1;
            while (bucketsB > 0 && i >= 0) {
                bucketsB--;
                sumB += berries[i];
                i--;
            }
        }

        return sumB;
    }

    // static class Arbiter implements Comparator<Integer> {
    //     public int compare(Integer i1, Integer i2) {
    //         return Integer.compare(i1%bucketSize, i2%bucketSize);
    //     }
    // }
}
