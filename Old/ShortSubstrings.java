import java.util.*;
import java.io.*;

public class ShortSubstrings {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i=1;i<=t;i++) {
            char[] string = br.readLine().toCharArray();
            // if (string.length > 2) {
                for (int j = 2; j <= string.length-1; j++) {
                    if (j%2==0) string[j]='0';
                }
            // }
            for (int j = 0; j <= string.length-1; j++) {
                if(string[j]!='0')pw.print(string[j]);
            }
            pw.println();
        }

        br.close(); pw.close();
    }
}
