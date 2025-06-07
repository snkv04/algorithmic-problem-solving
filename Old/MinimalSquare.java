import java.util.*;
import java.io.*;

public class MinimalSquare {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            int w = Math.max(a, b);
            int h = Math.min(a, b);
            pw.println(Math.max(w, 2*h) * Math.max(w, 2*h));
        }

        br.close(); pw.close();
    }
}
