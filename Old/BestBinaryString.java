import java.util.*;
import java.io.*;

public class BestBinaryString {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            char[]s = br.readLine().toCharArray();
            char[] newS = new char[s.length];
            newS[0] = s[0]=='?'?'0':s[0];
            for (int j = 1; j <= s.length-1; j++) {
                if (s[j]=='?') {
                    if (newS[j-1]=='0')newS[j]='0';
                    else newS[j]='1';
                } else {
                    newS[j] = s[j];
                }
            }
            pw.println(newS);
        }

        br.close(); pw.close();
    }
}
