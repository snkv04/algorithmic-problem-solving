import java.util.*;
import java.io.*;

public class UncowedForces {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int[] x = {500,1000,1500,2000,2500};
        int[] m = new int[5];
        for (int i = 0; i <= 4; i++) m[i] = sc.nextInt();
        int[] w = new int[5];
        for (int i = 0; i <= 4; i++) w[i] = sc.nextInt();
        int sum = 0;
        for (int i = 0; i <= 4; i++) {
            sum += Math.max(x[i] * 3 / 10, (x[i]/250)*(250-m[i]) - 50*w[i]);
        }
        sum += 100 * sc.nextInt() - 50 * sc.nextInt();
        pw.println(sum);

        sc.close(); pw.close();
    }
}
