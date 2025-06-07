import java.util.*;
import java.io.*;

public class LuoTianyiPalindromeString {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            char[] a = br.readLine().toCharArray();
            int ans = -1;
            for (int j = 0; j <= a.length - 1; j++) {
                if (a[0] != a[j]) {
                    ans = a.length-1;;
                    break;
                }
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
