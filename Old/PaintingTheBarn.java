import java.util.*;
import java.io.*;

public class PaintingTheBarn {
    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("paintbarn.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("paintbarn.out")));

        // to speed up how fast we apply each paint box and do the final single query,
        // we can have the prefix sum be the final paint matrix and have each
        // paint box be represented by its corners; while keeping in mind that we
        // are 1-indexing and having dummy 0s on the top and left AND that the coordinates
        // are the corner points and not corner boxes, if x1, y1, x2, and y2 are the corners,
        // then when applying a paint box, since the matrix is initialized as all 0s,
        // we can increment (x1,y1), decrement (x1,y2) and (x2, y1), and increment
        // (x2,y2); then, doing the prefix sum will result in the final paint coats :)
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int k = Integer.parseInt(line[1]);
        int[][] wall = new int[1002][1002];
        for (int i = 1; i <= n; i++) {
            line = br.readLine().split(" ");
            int x1 = Integer.parseInt(line[0]) + 1;
            int y1 = Integer.parseInt(line[1]) + 1;
            int x2 = Integer.parseInt(line[2]) + 1;
            int y2 = Integer.parseInt(line[3]) + 1;
            wall[x1][y1]++;
            wall[x1][y2]--;
            wall[x2][y1]--;
            wall[x2][y2]++;
        }

        int[][] prefix = new int[1002][1002];
        int count = 0;
        for (int i = 1; i <= 1001; i++) {
            for (int j = 1; j <= 1001; j++) {
                prefix[i][j] = wall[i][j] + prefix[i-1][j] + prefix[i][j-1]
                    - prefix[i-1][j-1];
                if (prefix[i][j] == k) count++;
            }
        }
        pw.println(count);

        br.close(); pw.close();
    }
}
