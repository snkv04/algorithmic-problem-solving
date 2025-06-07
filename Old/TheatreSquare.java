import java.util.*;
import java.io.*;

public class TheatreSquare {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        double n = sc.nextInt();
        double m = sc.nextInt();
        long a = sc.nextLong();
        long ans = (long) Math.ceil(n/a) * (long) Math.ceil(m/a);
        pw.println(ans);

        sc.close(); pw.close();
    }
}
