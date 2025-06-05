import java.util.*;
import java.io.*;

public class BlackboardList {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // if there is any negative number, it cannot be reached by taking the
        //// distance between any two values, so it has to be one of the original numbers
        // if there aren't any negative numbers, then the maximum number cannot be
        //// reached by taking the distance between any smaller nonnegative integers,
        //// so it has to be one of the original numbers
        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int max = Integer.MIN_VALUE;
            boolean negative_present = false;
            for (int value : a) {
                if (value < 0) {
                    pw.println(value);
                    negative_present = true;
                    break;
                } else {
                    max = Math.max(max, value);
                }
            }
            if (!negative_present) pw.println(max);
        }

        br.close(); pw.close();
    }
}
