import java.util.*;
import java.io.*;

public class Elephant {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int ans = 0;
        while (n>0) {
            ans++;
            n-=5;
        }
        pw.print(ans);

        br.close(); pw.close();
    }
}
