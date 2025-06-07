import java.util.*;
import java.io.*;

public class MakingTowers {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            ArrayList<Integer>[] positions = new ArrayList[n];
            for (int i = 0; i <= n-1; i++) positions[i] = new ArrayList<>();
            for (int i = 0; i <= n-1; i++) {
                positions[a[i]-1].add(i);
            }

            int[] answers = new int[n];
            for (int i = 0; i <= n-1; i++) {
                if (positions[i].size() >= 1) {
                    answers[i] = 1;
                    // int last = positions[i].get(0);
                    for (int j = 1; j <= positions[i].size()-1; j++) {
                        if ((positions[i].get(j) - positions[i].get(j-1) - 1)%2 == 0) answers[i]++;
                    }
                }
            }
            for (int ans : answers) pw.print(ans + " ");
            pw.println();
        }

        br.close(); pw.close();
    }
}
