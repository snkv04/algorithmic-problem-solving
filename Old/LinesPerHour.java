import java.util.*;
import java.io.*;

public class LinesPerHour {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] asdf = br.readLine().split(" ");
        int n = Integer.parseInt(asdf[0]), total = Integer.parseInt(asdf[1])*5;
        int[] times = new int[n];
        for (int i = 0; i <= n-1; i++) times[i] = Integer.parseInt(br.readLine());
        Arrays.sort(times);

        int count = 0, time = 0;
        for (int i = 0; i <= n-1; i++) {
            if (time + times[i] <= total) {time+=times[i];count++;}
            else break;
        }
        pw.println(count);
    }
}