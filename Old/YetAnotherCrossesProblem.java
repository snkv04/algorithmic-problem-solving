import java.util.*;
import java.io.*;

public class YetAnotherCrossesProblem {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int q = Integer.parseInt(br.readLine());
        for (int i = 1; i <= q; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            char[][] grid = new char[n][m];
            int[] whitePerRow = new int[n];
            int[] whitePerColumn = new int[m];
            for (int j = 0; j <= n-1; j++) {
                char[] gridLine = br.readLine().toCharArray();
                for (int k = 0; k <= m-1; k++) {
                    grid[j][k] = gridLine[k];
                    if (grid[j][k] == '.') {
                        whitePerRow[j]++;
                        whitePerColumn[k]++;
                    }
                }
            }

            int min = Integer.MAX_VALUE;
            for (int j = 0; j <= n-1; j++) {
                for (int k = 0; k <= m-1; k++) {
                    int required = 0;
                    required += whitePerRow[j];
                    required += whitePerColumn[k];
                    if (grid[j][k]=='.') {
                        required--; // because it's double counted
                    }
                    min = Math.min(min, required);
                }
            }
            pw.println(min);
        }

        br.close(); pw.close();

        // a correct brute force solution would be to check each cell and see
        // how many paint operations it would take for a cross to be established with
        // that point at its center. however, there are n*m centers, and each one
        // would require going all along the left-to-right axis and vertically as well
        // for each cell, so this would be O((n*m)*(n+m)). it would be more convenient
        // to do each one in O(1), which is possible. we can store the number of white
        // cells (or black cells) in each row and column, and for each cell we are checking,
        // we can check to see how many white cells need to be painted to form a cross.
        // also, this does take care of special cases like white cells overlapping
        // the horizontal black line and the vertical black line for each cell being checked,
        // since we are checking every single possible cross so those won't be missed
        // like a more sketchy solution might do.
    }
}
