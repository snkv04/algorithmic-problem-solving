import java.util.*;
import java.io.*;

public class GrasshopperOnALine {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <= t; i++){
            int x = sc.nextInt(), k = sc.nextInt();
            if (x%k==0) {
                pw.println(2);
                pw.println(x-1+" "+1);
            } else {
                pw.println(1);
                pw.println(x);
            }
        }

        sc.close(); pw.close();
    }
}
