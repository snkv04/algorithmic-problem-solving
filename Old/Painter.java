import java.util.*;
import java.io.*;

public class Painter {
    static char[] p;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            p = br.readLine().toCharArray();
            int totalStrokes = solve(new Character[] {'R', 'O', 'P', 'A'})
                + solve(new Character[] {'Y', 'O', 'G', 'A'})
                + solve(new Character[] {'B', 'P', 'G', 'A'});
            System.out.println("Case #" + i + ": " + totalStrokes);
        }

        br.close(); pw.close();
    }

    public static int solve(Character[] primaryColor) {
        int strokes = 0;
        int mostRecent = -2;
        for (int i = 0; i <= p.length - 1; i++) {
            if (Arrays.asList(primaryColor).contains(p[i])) {
                if (mostRecent != i-1) strokes++;
                mostRecent = i;
            }
        }
        return strokes;
    }
}
