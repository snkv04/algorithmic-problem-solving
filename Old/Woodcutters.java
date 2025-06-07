import java.util.*;
import java.io.*;

public class Woodcutters {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[][][] memo = new int[n+1][3][2];
        for (int i = 0; i <= 2; i++) memo[0][i][1] = (int)-2e9;
        for (int i = 1; i <= n; i++) {
            String[] line = br.readLine().split(" ");
            int x = Integer.parseInt(line[0]);
            int h = Integer.parseInt(line[1]);
            for (int j = 0; j <= 2; j++) {
                memo[i][j][0] = -1;
                for (int k = 0; k <= 2; k++) {
                    if (j==1) {
                        memo[i][j][1] = x;
                        if (memo[i-1][k][1] < memo[i][j][1])
                            memo[i][j][0] = Math.max(memo[i][j][0], memo[i-1][k][0]);
                    } else if (j==0) {
                        memo[i][j][1] = x; // ohhh
                        if (memo[i-1][k][1] < x-h)
                            memo[i][j][0] = Math.max(memo[i][j][0], memo[i-1][k][0]+1);
                    } else {
                        memo[i][j][1] = x+h;
                        if (memo[i-1][k][1] < x) memo[i][j][0] = Math.max(memo[i][j][0], memo[i-1][k][0]+1);
                    }
                }
                if (memo[i][j][0]==-1) memo[i][j][1] = (int)2e9+7;
            }
        }
        int ans = Math.max(memo[n][0][0], Math.max(memo[n][1][0], memo[n][2][0]));
        pw.println(ans);

        br.close(); pw.close();
    }

    // // // //

    static class Multiset {
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }
}
