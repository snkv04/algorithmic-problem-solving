import java.util.*;
import java.io.*;

public class MaximumProduct {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            Integer[] a = new Integer[n];
            boolean notAllNegatives = false;
            for (int i = 0; i <= n-1; i++) {
                a[i] = sc.nextInt();
                if (a[i] >= 0) notAllNegatives = true;
            }
            Arrays.sort(a, new Arbiter());
            // pw.println(Arrays.toString(a));
            if (!notAllNegatives) {
                long product = 1;
                for (int i = 0; i <= 4; i++) product *= a[i];
                pw.println(product);
                continue;
            }

            // long product = 1;
            // int[] vals = new int[5];
            // int negatives = 0;
            // for (int i = 0; i <= 4; i++) {
            //     vals[i] = a[n-1-i];
            //     if (a[n-1-i]<0) {
            //         negatives++;
            //     }
            // }
            long product = 1;
            for (int i = n-1; i >= n-5; i--) {
                product *= a[i];
            }

            // if (negatives%2==1) {
            //     // int ind = -1;
            //     // for (int i = 4; i >= 0; i--) {
            //     //     if (vals[i]<0) {
            //     //         ind = i;
            //     //         break;
            //     //     }
            //     // }
            //     // int largestPos = -1;
            //     // for (int i = n-6; i >= 0; i--) {
            //     //     if (a[i]>=0) {
            //     //         largestPos = a[i];
            //     //         break;
            //     //     }
            //     // }
            //     // if (largestPos != -1) a[ind] = largestPos;
            // }

            if (product < 0) {
                for (int i = n-1; i >= n-5; i--) {
                    long tempProduct = 1;
                    for (int j = n-1; j >= n-5; j--) {
                        if (j!=i) tempProduct *= a[j];
                    }

                    for (int j = n-6; j >= 0; j--) {
                        product = Math.max(product, tempProduct * a[j]);
                    }
                }
            }
            pw.println(product);
        }

        sc.close(); pw.close();
    }

    static class Arbiter implements Comparator<Integer> {
        public int compare(Integer i1, Integer i2) {
            if (Math.abs(i1) != Math.abs(i2)) return Integer.compare(Math.abs(i1), Math.abs(i2));
            else return Integer.compare(i1, i2);
        }
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
