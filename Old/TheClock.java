import java.util.*;
import java.io.*;

public class TheClock {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        boolean[] isPalindrome = new boolean[1440];
        HashMap<String, Integer> map = new HashMap<>();
        for (int i = 0; i <= 1440-1; i++) {
            int hours = i/60;
            int minutes = i - (hours*60);
            String asString = (hours<10?("0"+hours):(""+hours)) + ":"
                + (minutes<10?("0"+minutes):(""+minutes));
            boolean works = asString.charAt(0) == asString.charAt(4)
                && asString.charAt(1) == asString.charAt(3);
            isPalindrome[i] = works;
            map.put(asString, i);
        }

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            String string = line[0];
            int s = map.get(string);
            int x = Integer.parseInt(line[1]);
            int ans = 0;
            int curr = s;
            while (true) {
                // pw.println(asString(curr));
                // pw.println(curr);
                ans += isPalindrome[curr]?1:0;
                curr += x;
                curr %= 1440;
                if (curr==s) break;
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }

    static String asString(int time) {
        int hours = time/60;
        int minutes = time - (hours*60);
        return (hours<10?("0"+hours):(""+hours)) + ":"
                + (minutes<10?("0"+minutes):(""+minutes));
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
