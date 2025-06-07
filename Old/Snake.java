import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class Snake {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};
    static int[][] grid;
    static int applei, applej;
    static int r, c;
    static int length;

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
        /*
         * you can't go back directly on the head (unless you're length 1)
         * 
         */

        String[] s = br.readLine().split(" ");
        r = Integer.parseInt(s[0]); c = Integer.parseInt(s[1]);
        grid = new int[r][c];
        int headi = -1, headj = -1;
        length = 0;
        int camefromi = -1000, camefromj = -1000;
        for (int i = 0; i < r; i++) {
            char[] arr = br.readLine().toCharArray();
            for (int j = 0; j < c; j++) {
                if (arr[j] == '.' || arr[j] == 'A') {
                    grid[i][j] = Integer.MAX_VALUE/2;
                } else if (arr[j]-'0'>=0 && arr[j]-'0'<=9) {
                    grid[i][j] = arr[j] - '0';
                    length = Math.max(length, 1 + arr[j] - '0');
                } else {
                    grid[i][j] = (arr[j]-'a') + 10;
                    length = Math.max(length, 1 + (arr[j]-'a') + 10);
                }

                if (arr[j] == 'A') {
                    applei = i;
                    applej = j;
                }
                if (arr[j] == '0') {
                    headi = i;
                    headj = j;
                    length = Math.max(length, 1);
                }
                if (arr[j] == '1') {
                    camefromi = i;
                    camefromj = j;
                }
            }
        }
        // for (int i = 0; i < r; i++) pw.println(Arrays.toString(grid[i]));
        // pw.println("headi = "+headi+", headj="+headj);
        // pw.println("applei="+applei+", applej="+applej);
        // pw.println("length = "+length);
        // pw.println("camefromi="+camefromi+", camefromj="+camefromj);

        pw.println(dfs(headi, headj, 0, camefromi, camefromj) ? 1 : 0);
    }

    static boolean dfs(int i, int j, int step, int camefromi, int camefromj) {
        if (step <= -1 * r * c - 5) return false;
        if (i == applei && j == applej) {
            return true;
        }
        int newstep = step - 1;
        for (int k = 0; k <= 3; k++) {
            int newi = i + di[k];
            int newj = j + dj[k];
            if (newi == camefromi && newj == camefromj) {
                continue;
            }
            if (inBounds(newi, newj, r, c) && grid[newi][newj] >= newstep + length) {
                int before = grid[newi][newj];
                grid[newi][newj] = newstep;
                // pw.println("going from ("+i+", "+j+") to ("+newi+", "+newj+")");
                if (dfs(newi, newj, newstep, i, j)) return true;
                grid[newi][newj] = before;
            }
        }
        return false;
    }

    static boolean inBounds(int i, int j, int r, int c) {
        return (i >= 0) && (i < r) && (j >= 0) && (j < c);
    }
}
