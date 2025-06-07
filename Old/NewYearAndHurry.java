import java.util.*;
import java.io.*;

public class NewYearAndHurry {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int k = Integer.parseInt(line[1]);
        int sum = 0, ans = 0;
        for (int i = 1; i <= n; i++) {
            if (sum + 5*i <= 240-k) {
                sum += 5*i;
                ans = i;
            } else
                break;
        }
        pw.println(ans);

        br.close(); pw.close();
    }
}
