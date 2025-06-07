import java.util.*;
import java.io.*;

public class GameWithBoard {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            if (n <= 4) pw.println("Bob");
            else pw.println("Alice");
        }

        br.close(); pw.close();
    }
}
