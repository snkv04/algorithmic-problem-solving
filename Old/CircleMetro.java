import java.util.*;
import java.io.*;

public class CircleMetro {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int a = sc.nextInt();
        int x = sc.nextInt();
        int b = sc.nextInt();
        int y = sc.nextInt();
        int dan = a;
        int vlad = b;
        boolean works = false;
        while (true) {
            if (dan==vlad) {
                works = true;
                break;
            }
            if (dan==x || vlad==y) {
                break;
            }
            if (dan==n) dan = 1;
            else dan++;
            if (vlad == 1) vlad = n;
            else vlad--;
        }
        pw.println(works?"YES":"NO");

        sc.close(); pw.close();
    }
}
