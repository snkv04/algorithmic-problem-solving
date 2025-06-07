import java.util.*;
import java.io.*;

public class MarketingScheme {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.valueOf(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int l = Integer.valueOf(line[0]);
            int r = Integer.valueOf(line[1]);
            pw.println(r < 2 * l ? "yes" : "no");
        }

        br.close(); pw.close();
    }
}
