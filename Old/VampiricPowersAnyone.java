import java.util.*;
import java.io.*;

public class VampiricPowersAnyone {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            boolean[] canMake = new boolean[256];
            int prefixxor = 0;
            canMake[0] = true;
            int maxSubarrayXOR = 0;
            for (int i = 0; i <= n-1; i++) {
                prefixxor = prefixxor ^ a[i];
                // canMake[prefixxor] = true;
                for (int j = 0; j <= (1<<8)-1; j++) {
                    if (canMake[j]) {
                        maxSubarrayXOR = Math.max(maxSubarrayXOR, prefixxor ^ j);
                    }
                }
                canMake[prefixxor] = true;
            }
            pw.println(maxSubarrayXOR);
        }

        br.close(); pw.close();
    }
}
