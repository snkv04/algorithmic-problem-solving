import java.util.*;
import java.io.*;

public class TheLakes {
    static int n, m;
    static int[][] grid;
    static boolean visited[][];
    static int sumDepths;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0 ){
            String[] line = br.readLine().split(" ");
            n = Integer.parseInt(line[0]);
            m = Integer.parseInt(line[1]);
            grid = new int[n][m];
            for (int i = 0; i <= n-1; i++) {
                grid[i] = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            }

            int maxSum = 0;
            visited = new boolean[n][m];
            for (int i = 0; i <= n-1; i++) {
                for (int j = 0; j <= m-1; j++) {
                    sumDepths = 0;
                    dfs(i, j);
                    maxSum = Math.max(maxSum, sumDepths);
                }
            }
            pw.println(maxSum);
        }

        br.close(); pw.close();
    }

    static void dfs(int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= m) return;
        if (visited[i][j]) return;
        if (grid[i][j]==0) return;

        visited[i][j] = true;
        sumDepths += grid[i][j];
        dfs(i, j+1);
        dfs(i, j-1);
        dfs(i-1, j);
        dfs(i+1, j);
    }
}
