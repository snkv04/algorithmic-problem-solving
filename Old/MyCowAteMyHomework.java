import java.util.*;
import java.io.*;

public class MyCowAteMyHomework {
    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("homework.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("homework.out")));

        int n = Integer.parseInt(br.readLine());
        int[] grades = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        // keep suffix sum and min arrays separate to not mess up suffix array,
        // as min may change over indices
        int[] suffix = new int[n];
        int[] min = new int[n];
        suffix[n-1] = grades[n-1]; min[n-1] = grades[n-1];
        for (int i = n-2; i >= 0; i--) {
            suffix[i] = suffix[i+1] + grades[i];
            min[i] = Math.min(min[i+1], grades[i]);
        }

        double maxAvg = (double)(suffix[1] - min[1]) / (n - 1 - 1);

        for (int k = 2; k <= n-2; k++) {
            maxAvg = Math.max(maxAvg, (double) (suffix[k] - min[k]) / (n - k - 1));
        }

        for (int k = 1; k <= n-2; k++) {
            if ((double) (suffix[k] - min[k]) / (n-k-1) == maxAvg) {
                pw.println(k);
            }
        }

        br.close(); pw.close();
    }
}
