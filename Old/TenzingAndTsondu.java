import java.util.*;
import java.io.*;

public class TenzingAndTsondu {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            Multiset a = new Multiset();
            Multiset b = new Multiset();
            line = br.readLine().split(" ");
            for (int j = 0; j<=n-1;j++) {
                a.add(Integer.parseInt(line[j]));
            }
            line = br.readLine().split(" ");
            for (int j = 0;j<=m-1;j++) {
                b.add(Integer.parseInt(line[j]));
            }

            // if (a.multiset.firstKey() > b.multiset.lastKey()) {
            //     pw.println("Tsondu");
            // } else if (a.multiset.lastKey() < b.multiset.firstKey()) {
            //     pw.println("Tenzing");
            // }
            int turn = 0;
            while (!a.multiset.isEmpty() && !b.multiset.isEmpty()) {
                if (turn == 0) {
                    int amax = a.multiset.lastKey();
                    int bmin = b.multiset.firstKey();
                    if (amax == bmin) {
                        a.remove(amax);
                        b.remove(bmin);
                    } else if (amax > bmin) {
                        a.add(amax-bmin);
                        a.remove(amax);
                        b.remove(bmin);
                    } else {
                        b.add(bmin-amax);
                        b.remove(bmin);
                        a.remove(amax);
                    }
                } else {
                    int bmax = b.multiset.lastKey();
                    int amin = a.multiset.firstKey();
                    if (bmax==amin) {
                        b.remove(bmax);
                        a.remove(amin);
                    } else if (bmax > amin) {
                       b.add(bmax-amin);
                       b.remove(bmax);
                       a.remove(amin);
                    } else {
                        a.add(amin-bmax);
                        a.remove(amin);
                        b.remove(bmax);
                    }
                }
                turn = 1 - turn;
            }
            if (a.multiset.isEmpty() && b.multiset.isEmpty()) pw.println("Draw");
            else if (a.multiset.isEmpty()) pw.println("Tenzing");
            else pw.println("Tsondu");
        }

        br.close(); pw.close();
    }

    static class Multiset {
        TreeMap<Integer, Integer> multiset;

        public Multiset() {
            multiset = new TreeMap<>();
        }

        public void add(int x) {
            if (multiset.containsKey(x)) {
                multiset.put(x, multiset.get(x)+1);
            } else {
                multiset.put(x, 1);
            }
        }

        public void remove(int x) {
            multiset.put(x, multiset.get(x) - 1);
            if (multiset.get(x) == 0){
                multiset.remove(x);
            }
        }
    }
}
