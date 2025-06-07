import java.util.*;
import java.io.*;

public class TwoSubstrings {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        char[] s = br.readLine().toCharArray();
        if (s.length==1) {
            pw.println("NO");
            pw.close();
            return;
        }
        boolean ab1 = false, ba1 = false;
        for (int i = 1; i <= s.length-1; i++) {
            if (s[i-1]=='A'&&s[i]=='B'&&!ab1) {
                ab1 = true;
                i++;
            } else            if (s[i-1]=='B'&&s[i]=='A'&&!ba1) {
                ba1 = true;
                i++;
            }
        }
        boolean ab2=false, ba2 = false;
        for (int i = s.length-2; i >= 0; i--) {
            if (s[i]=='A'&&s[i+1]=='B'&&!ab2) {
                ab2 = true;
                i--;
            } else if (s[i]=='B'&&s[i+1]=='A'&&!ba2) {
                ba2 = true;
                i--;
            }
        }
        pw.println((ab1&&ba1 || ab2&&ba2)?"YES":"NO");

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
