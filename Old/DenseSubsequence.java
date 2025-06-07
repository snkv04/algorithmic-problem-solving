import java.util.*;
import java.io.*;

public class DenseSubsequence {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int m = Integer.parseInt(br.readLine());
        char[] s = br.readLine().toCharArray();
        int n = s.length;
        int start = -1;
        ArrayList<Character> chosen = new ArrayList<Character>();
        while (start+m <= n-1) {
            int end = start+m;
            int minindex = -1;
            char minchar = 'z';
            for (int i = start+1; i <= end; i++) {
                if (s[i] <= minchar) {
                    minchar = s[i];
                    minindex = i;
                }
            }
            chosen.add(s[minindex]);
            start = minindex;
        }
        Collections.sort(chosen);
        for (char character : chosen) pw.print(character);

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
