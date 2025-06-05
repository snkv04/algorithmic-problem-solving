import java.util.*;
import java.io.*;

public class Allocation {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            Arrays.sort(a);
            int count = 0;
            for (int ai : a) {
                if (ai <= b) {
                    b -= ai;
                    count++;
                } else {
                    break;
                }
            }
            pw.println("Case #" + i + ": " + count);
        }

        br.close(); pw.close();
    }
}
