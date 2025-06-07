import java.util.*;
import java.io.*;

public class MirrorInTheString {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            char[] s = br.readLine().toCharArray();
            ArrayList<Character> half = new ArrayList<Character>();
            half.add(s[0]);
            for (int i = 1; i <= n-1; i++) {
                if (s[i]<=s[i-1]) {
                    half.add(s[i]);
                } else break;
            }
            char[] full = new char[2*half.size()];
            int j = 0;
            for (int i = 0; i <= half.size()-1; i++) { full[j] = half.get(i); j++; }
            for (int i = half.size()-1; i >= 0; i--) { full[j] = half.get(i); j++; }
            String small = "" + s[0] + s[0];
            String large = String.valueOf(full);
            pw.println(small.compareTo(large)>0 ? large : small);
        }

        br.close(); pw.close();
    }
}
