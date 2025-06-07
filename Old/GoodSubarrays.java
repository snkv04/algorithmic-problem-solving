import java.util.*;
import java.io.*;

public class GoodSubarrays {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split("")).mapToInt(Integer::parseInt).toArray();
            int[] prefsums = new int[n+1];
            HashMap<Integer, Integer> num = new HashMap<>();
            long ans = 0;
            for (int i = 1; i <= n; i++) {
                prefsums[i] = prefsums[i-1] + a[i-1];
                int leftVal = prefsums[i-1]-i+1;
                if (!num.containsKey(leftVal)) {
                    num.put(leftVal, 1);
                } else {
                    num.put(leftVal, num.get(leftVal)+1);
                }
                int rightVal = prefsums[i] - i;
                if (num.containsKey(rightVal)) {
                    ans += num.get(rightVal);
                }
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
