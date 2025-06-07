import java.util.*;
import java.io.*;

public class LittleGirlAndMaximumSum {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int k = Integer.parseInt(line[1]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Integer[] b = new Integer[n]; for (int i = 0; i <= n-1; i++) b[i] = a[i];
        int[] numQueries = new int[200001];
        for (int i = 1; i <= k; i++) {
            line = br.readLine().split(" ");
            int l = Integer.parseInt(line[0]);
            int r = Integer.parseInt(line[1]);
            numQueries[l-1]++;
            numQueries[r]--;
        }
        Integer[] numQueriesCorrected = new Integer[200001];
        numQueriesCorrected[0] = numQueries[0];
        for (int i = 1; i <= 200000; i++) {
            numQueriesCorrected[i] = numQueriesCorrected[i-1] + numQueries[i];
        }
        Arrays.sort(numQueriesCorrected);
        Arrays.sort(b);
        long sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += numQueriesCorrected[200001-i] * (long) b[n-i];
        }
        pw.println(sum);

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
