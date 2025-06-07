import java.util.*;
import java.io.*;

public class MilkPails {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("pails.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("pails.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        String[] split = br.readLine().split(" ");
        int x = Integer.parseInt(split[0]);
        int y = Integer.parseInt(split[1]);
        int m = Integer.parseInt(split[2]);

        int max = 0;
        for (int i = 0; i <= (m - (m % x)) / x; i++) {
            int milk = i * x;
            while(milk + y <= m) {
                milk += y;
            }
            max = Math.max(max, milk);
        }

        pw.println(max);

        br.close(); pw.close();
    }
}
