import java.util.*;
import java.io.*;

public class APileOfStones {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        char[] s = br.readLine().toCharArray();
        boolean ending = true;
        int ans = 0;
        int balance = 0;
        for (int i = n-1; i >= 0; i--) {
            if (ending) {
                if (s[i]=='+') {
                    ans++;
                } else {
                    ending = false;
                    balance--;
                }
            } else {
                if (s[i]=='+') balance++;
                else balance--;
            }
        }
        if (s[0]=='-') balance++;
        pw.print(Math.max(balance, 0)+ans);

        br.close(); pw.close();
    }
}
