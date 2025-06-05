import java.util.*;
import java.io.*;

public class ABPalindrome {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            int n = a+b;
            char[] s = br.readLine().toCharArray();
            int counta = 0, countb = 0;
            boolean works = true;
            for (int i = 0; i <= n-1; i++) {
                char curr = s[i];
                char other = s[n-1-i];
                if (curr=='?') {
                    if (other=='0') {
                        s[i] = '0';
                    } else if (other=='1') {
                        s[i] = '1';
                    } else {
                        continue;
                    }
                }
            }
            for (int i = 0; i <= n/2-1 && works; i++) {
                if (s[i]=='0') {
                    if (s[n-1-i]=='0') {
                        counta+=2;
                    } else {
                        works = false;
                    }
                } else if (s[i]=='1') {
                    if (s[n-1-i]=='1') {
                        countb += 2;
                    } else {
                        works = false;
                    }
                }
            }
            if (n%2==1) {
                if (s[(n-1)/2]=='0') counta++;
                else if (s[(n-1)/2]=='1') countb++;
            }
            if (counta > a || countb > b) works = false;
            // pw.println(s);
            // pw.println(works + " so far");
            // pw.println(counta + " " + countb);

            for (int i = (n-1)/2; i >= 0 && works; i--) {
                if (s[i]=='?') {
                    if (counta <= a-2) {
                        counta+=2;
                        s[i]='0';
                        s[n-1-i]='0';
                    } else if (countb <= b-2) {
                        countb+=2;
                        s[i]='1';
                        s[n-1-i]='1';
                    } else if (i==(n-1)/2 && n%2==1) {
                        if (counta <= a-1) {
                            s[i]='0';
                        } else if (countb <= b-1) {
                            s[i]='1';
                        } else {
                            works = false;
                        }
                    } else {
                        works = false;
                    }
                }
            }
            if (works) pw.println(s);
            else pw.println(-1);
            // pw.println();
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
