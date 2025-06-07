import java.util.*;
import java.io.*;

public class PatchoulisMagicalTalisman {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int numEven = 0;
            for (int i = 0; i <= n-1; i++) {
                if (a[i]%2==0) {
                    numEven++;
                }
            }
            if (numEven < n) {
                pw.println(numEven);
                continue;
            }

            // all of the numbers are even
            int min = Integer.MAX_VALUE;
            for (int i = 0; i <= n-1; i++) {
                min = Math.min(min, numToOdd(a[i]));
            }
            pw.println(n-1+min);
        }

        br.close(); pw.close();
    }

    static int numToOdd(int x) {
        int ans = 0;
        while (x%2==0) {
            ans++;
            x /= 2;
        }
        return ans;
    }
}
