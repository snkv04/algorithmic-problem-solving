import java.util.*;
import java.io.*;

public class FromSToT {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int q = Integer.parseInt(br.readLine());
        while (q-->0) {
            char[] s = br.readLine().toCharArray();
            char[] t = br.readLine().toCharArray();
            char[] p = br.readLine().toCharArray();
            Multiset pchars = new Multiset();
            for (char letter : p) pchars.add(letter);

            if (s.length > t.length || p.length + s.length < t.length) {
                pw.println("NO");
                continue;
            }
            int i = 0, j=0;
            ArrayList<Character> need = new ArrayList();
            for (i = 0; i <= t.length-1; i++) {
                if (j >= s.length || s[j] != t[i]) {
                    need.add(t[i]);
                } else {
                    j++;
                }
            }

            if (j!=s.length) {
                pw.println("NO");
                continue;
            }
            boolean works = true;
            for (char letter : need) {
                if (pchars.mset.containsKey(letter)) {
                    pchars.remove(letter);
                } else {
                    works = false;
                    break;
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }

    // // // //

    static class Multiset {
        TreeMap<Character, Integer> mset = new TreeMap<>();

        public void add(char x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(char x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        // public void add(int x, int q) {
        //     // q for quantity
        //     if (mset.containsKey(x)) {
        //         mset.put(x, mset.get(x) + q);
        //     } else {
        //         mset.put(x, q);
        //     }
        // }
    }
}
