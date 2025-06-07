import java.util.*;
import java.io.*;

public class UniqueNumber {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int x = Integer.parseInt(br.readLine());
            Stack<Integer> s = new Stack<Integer>();
            int digit = 9;
            while (x>0&&digit>0) {
                s.add(Math.min(x, digit));
                x-=Math.min(x, digit);
                digit--;
            }
            if (x==0) {
                while (!s.isEmpty()) {
                    pw.print(s.pop());
                }
            } else pw.print(-1);
            pw.println();
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
