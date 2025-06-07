import java.util.*;
import java.io.*;

public class SubtractionGame {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0)
            pw.println(sc.nextInt()+sc.nextInt());

        sc.close(); pw.close();
    }
}
