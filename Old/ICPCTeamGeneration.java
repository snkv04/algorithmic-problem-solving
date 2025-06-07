import java.util.*;
import java.io.*;

public class ICPCTeamGeneration {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        boolean[] used = new boolean[n];
        int[][] segments = new int[n][2];
        int ans = 0;
        for (int i =0 ; i <= n-1 ;i++){
            segments[i] = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            segments[i][0]--; segments[i][1]--;

            ArrayList<Integer> good = new ArrayList<>();
            for (int j = 0; j <= i-1; j++) {
                if (!used[j] && contains(segments[j][0], segments[j][1], i) && contains(segments[i][0], segments[i][1], j)) {
                    good.add(j);
                }
                if (good.size()==2) break;
            }

            if (good.size()==2) {
                int first = good.get(0), second = good.get(1);
                used[first] = true; used[second] = true; used[i] = true;
                ans++;
            }
        }
        // pw.println(Arrays.toString(used));
        pw.println(ans);
    }

    static boolean contains(int l, int r, int x) {
        return x <= r && x >= l;
    }
}