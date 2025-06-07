import java.util.*;
import java.io.*;

public class DeleteTwoElements {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            double sum = 0;
            for (int num : a) sum += num;

            double avg = sum / (double)n;
            long count = 0;
            Multiset previousElements = new Multiset();
            for (int i = 0; i <= n-1; i++) {
                double other = 2 * avg - a[i];
                if (previousElements.mset.containsKey(other)) {
                    count += previousElements.mset.get(other);
                }
                previousElements.add(a[i]);
            }
            pw.println(count);
        }

        br.close(); pw.close();
    }

    // // // //

    static class Multiset {
        TreeMap<Double, Integer> mset = new TreeMap<>();

        public void add(double x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(double x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }
    }
}
