import java.util.*;
import java.io.*;

public class PlayingWithGCD {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] b = new int[n+1];
            b[0] = a[0]; b[n] = a[n-1];
            for (int i = 1; i <= n-1; i++) {
                b[i] = a[i] * a[i-1] / gcd(a[i], a[i-1]);
            }

            boolean works = true;
            for (int i = 0; i <= n-1; i++) {
                if (a[i] != gcd(b[i], b[i+1])) {
                    works = false;
                    break;
                }
            }
            // pw.println(Arrays.toString(a));
            // pw.println(Arrays.toString(b));
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }

    static int gcd(int a, int b) {
        int max = Math.max(a, b);
        int min = Math.min(a, b);
        while (min != 0) {
            int temp = min;
            min = max % min;
            max = temp;
        }
        return max;
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
