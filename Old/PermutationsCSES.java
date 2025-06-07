import java.util.*;
import java.io.*;

public class PermutationsCSES {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        if (n == 1) {
            pw.print("1");
        } else if (n <= 3) {
            pw.print("NO SOLUTION");
        } else {
            int remaining = n % 4;
            ArrayDeque<Integer> result = new ArrayDeque<Integer>();
            for (int i = 1; i <= (n - remaining) / 4; i++) {
                result.addLast(4 * (i - 1) + 3);
                result.addLast(4 * (i - 1) + 1);
                result.addLast(4 * (i - 1) + 4);
                result.addLast(4 * (i - 1) + 2);
            }
            if (n % 4 == 1) result.addFirst(n);
            else if (n % 4 == 2) {
                result.addLast(n);
                result.addFirst(n-1);
            }
            else if (n % 4 == 3) {
                result.addLast(n);
                result.addLast(n-2);
                result.addFirst(n-1);
            }

            for (int j : result) {
                pw.print(j + " ");
            }
        }

        br.close(); pw.close();
    }
}
