import java.util.*;
import java.io.*;

public class SnowWalkingRobot {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int q = Integer.parseInt(br.readLine());
        for (int i = 1; i <= q; i++) {
            char[] instructions = br.readLine().toCharArray();
            int l = 0, r = 0, u = 0, d = 0;
            for (char character : instructions) {
                if (character=='L')l++;
                if (character=='R') r++;
                if (character=='U') u++;
                if (character=='D') d++;
            }

            if (Math.min(l, r) == 0) {
                if (u>=1 && d>=1) {
                    pw.println(2);
                    pw.println("UD");
                } else {
                    pw.println(0);
                    pw.println();
                }
            } else if (Math.min(u, d)==0) {
                if (l>=1 && r>=1) {
                    pw.println(2);
                    pw.println("LR");
                } else {
                    pw.println(0);
                    pw.println();
                }
            } else {
                int horizontal = Math.min(l, r);
                int vertical = Math.min(u, d);
                pw.println(2*horizontal + 2*vertical);
                for (int j = 1; j<=vertical; j++) {
                    pw.print('U');
                }
                for (int j = 1; j <= horizontal; j++) pw.print('R');
                for (int j = 1; j <= vertical; j++) pw.print('D');
                for (int j = 1; j <= horizontal; j++) pw.print('L');
                pw.println();
            }
        }

        br.close(); pw.close();
    }
}
