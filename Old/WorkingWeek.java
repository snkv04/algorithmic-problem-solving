import java.util.*;
import java.io.*;

public class WorkingWeek {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            long result = (n - 6) / 3;
            pw.println(result);
        }

        br.close(); pw.close();
    }
}
