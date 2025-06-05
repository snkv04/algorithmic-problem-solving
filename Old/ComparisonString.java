import java.util.*;
import java.io.*;

public class ComparisonString {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            char[] str = br.readLine().toCharArray();
            int longest = 1;
            int current = 1;
            for (int j=1; j <= n-1; j++) {
                if (str[j]==str[j-1]) {
                    current++;
                } else {
                    longest = Math.max(current, longest);
                    current = 1;
                }
            }
            longest = Math.max(current, longest);
            pw.println(longest+1);
        }

        br.close(); pw.close();
    }
}
