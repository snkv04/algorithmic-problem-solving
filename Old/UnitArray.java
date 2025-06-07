import java.util.*;
import java.io.*;

public class UnitArray {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int numPos = 0;
            int numNeg = 0;
            for (int val : a) {
                if (val > 0) numPos++;
                else numNeg++;
            }

            int ans = 0;
            if (numNeg %2 == 1) {
                numNeg--; numPos++;
                ans++;
            }
            while (numNeg > numPos) {
                numNeg -= 2;
                numPos += 2;
                ans += 2;
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
