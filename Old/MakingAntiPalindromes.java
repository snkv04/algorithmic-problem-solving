import java.util.*;
import java.io.*;

public class MakingAntiPalindromes {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            char[] s = br.readLine().toCharArray();
            if (n%2==1) {
                pw.println(-1);
                continue;
            }
            int[] count = new int[26];
            int[] pairs = new int[26];
            for (int i = 0; i <= n/2-1; i++) {
                count[s[i]-'a']++;
                count[s[n-1-i]-'a']++;
                if (s[i]==s[n-1-i]) pairs[s[i]-'a']++;
            }

            int maxCount = 0;
            for (int i = 0; i <= 25; i++) maxCount = Math.max(maxCount, count[i]);
            if (maxCount > n/2) {
                pw.println(-1); continue;
            }

            int ans = 0, left=-1, right=-2;
            boolean done = false;
            Arrays.sort(pairs);
            while (!done) {
                // for (int i = 0; i <= 25; i++) {
                //     if (pairs[i]>0) {
                //         left=i;
                //         break;
                //     }
                // }
                // if (left<0) {
                //     done = true;
                //     break;
                // }
                // for (int i = 25; i >= 0; i--) {
                //     if (pairs[i]>0) {
                //         right = i;
                //         break;
                //     }
                // }
                // if (right != left) {
                //     int detract = Math.min(pairs[left], pairs[right]);
                //     ans += detract;
                //     pairs[left]-=detract;
                //     pairs[right]-=detract;
                //     left = -1; right = -1;
                // } else {
                //     ans += pairs[left];
                //     done = true;
                // }
                if (pairs[24] > 0) {
                    int reduce = Math.min(pairs[24], pairs[25]);
                    ans += reduce;
                    pairs[24]-=reduce;
                    pairs[25]-=reduce;
                    Arrays.sort(pairs);
                } else {
                    ans += pairs[25];
                    done = true;
                }
            }
            pw.println(ans);
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
