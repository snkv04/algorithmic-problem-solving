import java.util.*;
import java.io.*;

public class BeforeAnExam {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int d = sc.nextInt();
        int sum = sc.nextInt();
        int[] mins = new int[d];
        int[] maxs = new int[d];
        for (int i = 0; i <= d-1; i++) {
            mins[i] = sc.nextInt();
            maxs[i] = sc.nextInt();
        }

        int[] hours = new int[d];
        for (int i = 0; i <= d-1 && sum > 0; i++) {
            sum -= mins[i];
            hours[i] = mins[i];
        }
        if (sum < 0) {
            pw.print("NO");
            pw.close();
            return;
        }
        for (int i = 0; i <= d-1 && sum > 0; i++) {
            hours[i] += Math.min(sum, maxs[i]-mins[i]);
            sum -= Math.min(sum, maxs[i]-mins[i]);
        }
        if (sum > 0) {
            pw.print("NO");
            pw.close();
            return;
        }
        pw.println("YES");
        for (int val : hours) pw.print(val + " ");

        sc.close(); pw.close();
    }
}
