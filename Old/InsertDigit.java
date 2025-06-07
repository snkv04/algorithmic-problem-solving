import java.util.*;
import java.io.*;

public class InsertDigit {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            char d = line[1].charAt(0);
            String num = br.readLine();
            boolean done = false;
            for (int j = 0; j <= n-1; j++) {
                if (d > num.charAt(j) && !done) {
                    pw.print(d);
                    done = true;
                }
                pw.print(num.charAt(j));
            }
            if (!done) pw.print(d);
            pw.println();
        }

        br.close(); pw.close();
    }
}
