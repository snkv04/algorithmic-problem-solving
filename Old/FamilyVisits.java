import java.util.*;
import java.io.*;

public class FamilyVisits {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;

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
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int d = Integer.parseInt(line[1]);
        int[][]messClean = new int[n+1][2];
        for (int i = 1;i <= n; i++) {
            messClean[i] = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        }
        int[] visits = new int[d+1];
        visits[0] = 0;
        for (int i =1; i <= d; i++) visits[i] = Integer.parseInt(br.readLine());

        boolean works = true;
        int ans = 0;
        for (int i = 1; i <= d && works; i++) {
            int start = visits[i-1]+1;
            int end = visits[i];
            int k = end;
            PriorityQueue<Integer> availableCleanings = new PriorityQueue<>(Comparator.comparingInt(o -> -o));
            int currentCleaning = 0;
            while (k >= start) {
                availableCleanings.add(messClean[k][1]);
                
                int mess = messClean[k][0];
                while (mess > currentCleaning) {
                    mess -= currentCleaning;
                    if (availableCleanings.isEmpty()) {
                        works = false;
                        break;
                    } else {
                        ans++;
                        currentCleaning = availableCleanings.poll();
                    }
                }
                if (currentCleaning >= mess) {
                    currentCleaning -= mess;
                }
                k--;

                if (works == false) break;
            }
        }
        pw.println(works?ans:-1);
    }
}
