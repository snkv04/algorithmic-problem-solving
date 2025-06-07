import java.util.*;
import java.io.*;

public class NewYearAndNorthPole {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int pos = 20000;
        boolean works = true;
        for (int i = 1; i <= n; i++) {
            String[] line = br.readLine().split(" ");
            int dist = Integer.parseInt(line[0]);
            String dir = line[1];
            if (dir.equals("East") || dir.equals("West")) {
                if (pos == 20000 || pos == 0) {
                    works = false;
                    break;
                }
            } else {
                dist *= dir.equals("North") ? 1 : -1;
                if (pos + dist > 20000) {
                    works = false;
                    break;
                } else if (pos + dist < 0) {
                    works = false;
                    break;
                } else {
                    pos += dist;
                }
            }
        }
        works = works && pos==20000;
        pw.println(works?"YES":"NO");

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
