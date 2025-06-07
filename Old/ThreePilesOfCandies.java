import java.util.*;
import java.io.*;

public class ThreePilesOfCandies {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int queries = sc.nextInt();
        for (int q = 1; q <= queries; q++) {
            long a = sc.nextLong();
            long b = sc.nextLong();
            long c = sc.nextLong();
            long min = Math.min(a, Math.min(b, c));
            long max = Math.max(a, Math.max(b, c));
            long med = a+b+c - min - max;

            long add = Math.min(max, med-min);
            min += add;
            max -= add;

            pw.println(min + (max/2));
        }

        sc.close(); pw.close();
    }
}
