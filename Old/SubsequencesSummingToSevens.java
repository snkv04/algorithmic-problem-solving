import java.util.*;
import java.io.*;

public class SubsequencesSummingToSevens {
    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("div7.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("div7.out")));

        int n = Integer.parseInt(br.readLine());
        int[] ids = new int[n];
        for (int i = 0; i <= n-1; i++) {
            ids[i] = Integer.parseInt(br.readLine());
        }

        int[] prefix = new int[n+1];
        for (int i = 1; i <= n; i++) {
            prefix[i] = (prefix[i-1] + ids[i-1]) % 7;
        }
        // pw.println(Arrays.toString(ids));
        // pw.println(Arrays.toString(prefix));

        int[] maxLength = new int[7];
        for (int i = 0; i <= 6; i++) {
            int leftI = -1;
            int rightI = -1;
            for (int j = 0; j <= n; j++) {
                if (prefix[j] == i) {
                    if (leftI == -1) {
                        leftI = j;
                    } else rightI = j;
                }
            }

            if (leftI != -1 && rightI != -1) maxLength[i] = rightI - leftI;
        }

        int max = -1;
        for (int element : maxLength) max = Math.max(max, element);
        pw.println(max);

        br.close(); pw.close();
    }
}
