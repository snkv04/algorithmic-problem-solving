import java.util.*;
import java.io.*;

public class XXXXX {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int sum = 0;
            for (int num : a) sum += num;
            if (sum % k != 0) {
                pw.println(n);
                continue;
            }

            int left = -1;
            for (int i = 0; i <= n-1; i++) {
                if (a[i] % k != 0) {
                    left = i+1;
                    break;
                }
            }
            int right = -1;
            for (int i = 0; i <= n-1; i++) {
                if (a[n-1-i] % k != 0) {
                    right = i+1;
                    break;
                }
            }
            pw.println((left==-1&&right==-1)?-1:(n-Math.min(left, right)));
        }

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
