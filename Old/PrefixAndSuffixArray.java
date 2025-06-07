import java.util.*;
import java.io.*;

public class PrefixAndSuffixArray {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            String[] strings = br.readLine().split(" ");
            Arrays.sort(strings, Comparator.comparingInt(obj -> obj.length()));
            pw.println(isReverse(strings[2*n-4], strings[2*n-3]) ? "YES" : "NO");
        }

        br.close(); pw.close();
    }

    // static boolean isPal(String s) {
    //     for (int i = 0; i <= s.length()/2; i++) {
    //         if (s.charAt(i) != s.charAt(s.length()-1-i)) return false;
    //     }
    //     return true;
    // }

    static boolean isReverse(String s1, String s2) {
        for (int i = 0; i <= s1.length()-1; i++) {
            if (s1.charAt(i) != s2.charAt(s2.length()-1-i)) return false;
        }
        return true;
    }
}
