import java.util.*;
import java.io.*;

public class Stripes {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            br.readLine();
            char[][] grid = new char[8][8];
            for (int i = 0; i <= 7; i++) {
                grid[i] = br.readLine().toCharArray();
            }

            int ans = -1;
            for (int i = 0; i <= 7; i++) {
                boolean works = true;
                for (int j = 0; j <= 7; j++) {
                    if (grid[i][j]!='R') {
                        works = false;
                        break;
                    }
                }
                if (works) { ans = 0; break;}
            }

            if (ans == -1)
            for (int j = 0; j <= 7; j++) {
                boolean works = true;
                for (int i = 0; i <= 7; i++) {
                    if (grid[i][j] != 'B') {
                        works = false;
                        break;
                    }
                }
                if (works) { ans = 1; break; }
            }

            if (ans == 0) pw.println('R');
            else pw.println('B');
        }

        br.close(); pw.close();
    }
}
