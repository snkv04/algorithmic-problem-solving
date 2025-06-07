import java.util.*;
import java.io.*;

public class NumberOfWays {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        long[] prefSums = new long[n];
        long[] sufsums = new long[n];
        prefSums[0] = a[0]; sufsums[n-1]=a[n-1];
        for (int i=1; i <= n-1; i++) {
            prefSums[i] = prefSums[i-1]+a[i];
            sufsums[n-1-i] = sufsums[n-i] + a[n-1-i];
        }
        if (prefSums[n-1]%3 != 0) {
            pw.println(0);
            pw.close();
            return;
        }

        long target = prefSums[n-1]/3;
        int[] numToRight = new int[n];
        numToRight[n-1] = sufsums[n-1]==target?1:0;
        for (int i = n-2; i >= 0; i--) {
            numToRight[i] = numToRight[i+1] + (sufsums[i]==target?1:0);
        }

        long ans = 0;
        for (int i = 0; i <= n-3; i++) {
            if (prefSums[i]==target) {
                ans += numToRight[i+2];
            }
        }
        pw.println(ans);

        br.close(); pw.close();
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
