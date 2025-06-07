import java.util.*;
import java.io.*;

public class Destroyer {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] l = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] count = new int[100];
            for (int j = 0; j <=n-1;j++) {
                count[l[j]]++;
            }
            boolean works = true;
            for (int j = 1; j <= 99; j++) {
                if (count[j] > count[j-1]) {
                    works = false;
                    break;
                }
            }
            pw.println(works ? "yes" : "no");
        }

        br.close(); pw.close();
    }
}
