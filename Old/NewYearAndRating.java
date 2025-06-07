import java.util.*;
import java.io.*;

public class NewYearAndRating {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[][] contests = new int[n][2];
        int leftmostDiv1 = (int)2e9, rightmostDiv2 = (int)-2e9, position = 0,
            lmd1index = -1, rmd2index = -1;
        for (int i = 0; i <= n-1; i++) {
            String[] line = br.readLine().split(" ");
            int delta = Integer.parseInt(line[0]);
            int division = Integer.parseInt(line[1]);
            if (division==1) {
                if (position < leftmostDiv1) {
                    leftmostDiv1 = position;
                    lmd1index = i;
                }
            } else {
                if (position > rightmostDiv2) {
                    rightmostDiv2 = position;
                    rmd2index = i;
                }
            }
            position += delta;
            contests[i][0] = delta;
            contests[i][1] = division;
        }
        if (rightmostDiv2 >= leftmostDiv1) {
            pw.println("Impossible");
        } else if (rmd2index == -1) {
            pw.println("Infinity");
        } else {
            position = 1899;
            for (int i = rmd2index; i <= n-1; i++) {
                position += contests[i][0];
            }
            pw.println(position);
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
