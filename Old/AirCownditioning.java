import java.util.*;
import java.io.*;

public class AirCownditioning {
    static int[] differences = new int[0];
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] pArray = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] tArray = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        differences = new int[n];
        for(int i = 0; i <= n-1; i++) {
            differences[i] = tArray[i] - pArray[i];
        }

        int ans = 0;
        for (int i = 0; i <= n-1; i++) {
            while (differences[i] > 0) {
                for (int j = i; j <= n-1 && differences[j] > 0; j++) {
                    differences[j]--;
                }
                ans++;
            }
            while (differences[i] < 0) {
                for (int j = i; j <= n-1 && differences[j] < 0; j++) {
                    differences[j]++;
                }
                ans++;
            }
        }
        pw.println(ans);

        br.close(); pw.close();
    }
}
