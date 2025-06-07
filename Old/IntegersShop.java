import java.util.*;
import java.io.*;

public class IntegersShop {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            TreeSet<Segment> byLeft = new TreeSet<>(new ByLeft());
            TreeSet<Segment> byRight = new TreeSet<>(new ByRight());
            TreeSet<Segment> bySize = new TreeSet<>(new ByLength());
            for (int i = 1; i <= n; i++) {
                String[] line = br.readLine().split(" ");
                int l = Integer.parseInt(line[0]);
                int r = Integer.parseInt(line[1]);
                int c = Integer.parseInt(line[2]);
                Segment s = new Segment(l, r, c);
                byLeft.add(s); byRight.add(s); bySize.add(s);
                pw.println((bySize.last().l<=byLeft.first().l&&bySize.last().r>=byRight.last().r
                    &&bySize.last().c<=byLeft.first().c+byRight.last().c)
                    ?bySize.last().c:(byLeft.first().c+byRight.last().c));
            }
        }

        br.close(); pw.close();
    }

    static class Segment {
        int l, r, c;
        
        public Segment(int l, int r, int c) {
            this.l = l;
            this.r = r;
            this.c = c;
        }
    }

    static class ByRight implements Comparator<Segment> {
        public int compare(Segment s1, Segment s2) {
            if (s1.r != s2.r) return Integer.compare(s1.r, s2.r);
            else return -Integer.compare(s1.c, s2.c);
        }
    }

    static class ByLeft implements Comparator<Segment> {
        public int compare(Segment s1, Segment s2) {
            if (s1.l != s2.l) return Integer.compare(s1.l, s2.l);
            else return Integer.compare(s1.c, s2.c);
        }
    }

    static class ByLength implements Comparator<Segment> {
        public int compare(Segment s1, Segment s2) {
            int len1 = s1.r-s1.l+1;
            int len2 = s2.r-s2.l+1;
            if (len1 != len2) return Integer.compare(len1, len2);
            else return -Integer.compare(s1.c, s2.c);
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
