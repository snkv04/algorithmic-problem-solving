import java.util.*;
import java.io.*;

public class IsItACat {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            char[] s = br.readLine().toLowerCase().toCharArray();
            if (s[0] != 'm') {
                pw.println("NO");
                continue;
            }
            char[] meow = {'m', 'e', 'o', 'w'};
            int j = 0;
            boolean works = true;
            for (int i = 1; i <= n-1; i++) {
                if (j==3) {
                    if (s[i] != meow[j]) {
                        works = false;
                        break;
                    }
                } else {
                    if (s[i] != meow[j]) {
                        if (s[i] != meow[j+1]) {
                            works = false;
                            break;
                        } else j++;
                    }
                }
            }
            pw.println(works&&j==3&&s[n-1]=='w'?"YES":"NO");
        }

        br.close(); pw.close();
    }
}
