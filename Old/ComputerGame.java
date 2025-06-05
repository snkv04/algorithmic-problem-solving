import java.util.*;
import java.io.*;

public class ComputerGame {
    static long n, k, a, b;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int q = Integer.parseInt(br.readLine());
        for (int i = 1; i <= q; i++) {
            String[] line = br.readLine().split(" ");
            k = Integer.parseInt(line[0]);
            n = Integer.parseInt(line[1]);
            a = Integer.parseInt(line[2]);
            b = Integer.parseInt(line[3]);
            long left = 0, right = n, ans = -1;
            while (left <= right) {
                long mid = (left+right)/2;
                if (check(mid)) {
                    ans = mid;
                    left = mid+1;
                } else {
                    right = mid-1;
                }
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }

    static boolean check(long numA) {
        if (numA > n) return false;
        if (k - (numA-1)*a <= a) return false;
        long charge = k - (numA * a);
        long remainingMoves = n - numA;
        if (charge <= b) {
            if (charge <= 0) return false;
            else if (remainingMoves==0) return true;
            else return false;
        }
        charge -= remainingMoves * b;
        if (charge > 0) return true;
        else return false;
    }
}
