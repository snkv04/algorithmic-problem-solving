import java.util.*;
import java.io.*;

public class APerfectlyBalancedString {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // pw.println((int)'a');
        // pw.println((int)'A');
        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            char[] s = br.readLine().toCharArray();
            HashSet<Integer> used = new HashSet<Integer>();
            ArrayList<Character> letters = new ArrayList<Character>();

            for (int i = 0; i <= s.length-1; i++) {
                if (!used.contains((int) s[i] - 97)) {
                    used.add((int)s[i] - 97);
                    letters.add(s[i]);
                }
            }
            boolean works = true;
            for (int i = 0; i <= s.length-1; i++) {
                if (s[i] != letters.get(i%letters.size())) {
                    works = false;
                    break;
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }
}
