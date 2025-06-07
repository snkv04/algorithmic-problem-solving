import java.util.*;
import java.io.*;

public class InSearchOfAnEasyProblem {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int[] a = new int[n]; for (int i = 0; i <= n-1; i++) a[i] = sc.nextInt();

        for (int num : a)
            if (num > 0) {
                pw.println("HARD");
                pw.close();
                return;
            }
        pw.println("EASY");

        sc.close(); pw.close();
    }
}
