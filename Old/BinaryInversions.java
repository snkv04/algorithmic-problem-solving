import java.util.*;
import java.io.*;

public class BinaryInversions {
    static int n;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            n = Integer.parseInt(br.readLine());
            int[] s = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            long max = Math.max(check(s, "left"), check(s, "right"));
            max = Math.max(max, check(s, ""));
            pw.println(max);
        }

        br.close(); pw.close();
    }

    static long check(int[] binary, String option) {
        int[] newBinary = new int[n];
        for (int i = 0; i <= n-1; i++) newBinary[i] = binary[i];
        if (option.equals("left")) for (int i = 0; i<=n-1; i++) { if (binary[i]==0) {newBinary[i]=1;break;} }
        else if (option.equals("right")) for (int i=n-1; i>=0; i--) if (binary[i]==1) {newBinary[i]=0;break;}

        int[] suffix0s = new int[binary.length];
        suffix0s[n-1] = newBinary[n-1]==0?1:0;
        for (int i = n-2; i >= 0; i--) {
            suffix0s[i] = suffix0s[i+1] + (newBinary[i]==0?1:0);
        }

        long sum = 0;
        for (int i = 0; i <= n-2; i++) {
            if (newBinary[i]==1) {
                sum += suffix0s[i+1];
            }
        }
        return sum;
    }
}
