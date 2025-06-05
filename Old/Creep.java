import java.util.*;
import java.io.*;

public class Creep {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            for (int i = 1; i <= Math.min(a, b); i++) {
                pw.print("01");
            }
            for (int i = 1; i <= Math.abs(b-a); i++) {
                if (b>a) pw.print(1);
                else pw.print(0);
            }
            pw.println();
        }

        br.close(); pw.close();
    }
}
