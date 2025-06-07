import java.util.*;
import java.io.*;

public class EightQueensValidator {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        HashSet<Integer> vertical = new HashSet<>(), horizontal = new HashSet<>(),
            downright = new HashSet<>(), downleft = new HashSet<>();
        char[][] grid = new char[8][8];
        for (int i = 0; i <= 7; i++) {
            grid[i] = br.readLine().toCharArray();
        }

        boolean works = true;
        int queens = 0;
        for (int i = 0; i <= 7 && works; i++) {
            for (int j = 0; j <= 7; j++) {
                if (grid[i][j] == '*') {
                    if (vertical.contains(j) || horizontal.contains(i) || downright.contains(i-j) || downleft.contains(i+j)) {
                        works = false;
                        break;
                    } else {
                        vertical.add(j);
                        horizontal.add(i);
                        downright.add(i-j);
                        downleft.add(i+j);
                        queens++;
                    }
                }
            }
        }
        pw.println((works&&queens==8)?"valid":"invalid");
    }
}
