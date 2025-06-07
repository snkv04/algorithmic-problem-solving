import java.util.*;
import java.io.*;

public class KarlCoder {
    static int MOD = (int) (1e9 + 7); // 998244353;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        long n = -1;
        long l = 0, r = 2;
        HashMap<Long, Integer> map = new HashMap<>();
        while (true) {
            System.out.println("buf["+r+"]");
            int result = Integer.parseInt(br.readLine());
            map.put(r, result);
            if (result != 0) r *= 2;
            else break;
        }
        while (l <= r) {
            long mid = (l+r)/2;
            int result;
            if (map.containsKey(mid)) result = map.get(mid);
            else {
                System.out.println("buf["+mid+"]");
                System.out.flush();
                System.out.flush();
                System.out.flush();
                System.out.flush();
                result = Integer.parseInt(br.readLine());
            }
            if (result == 0) {
                r = mid-1;
            } else {
                n = mid;
                l = mid+1;
            }
        }
        System.out.println("strlen(buf) = " + (n+1));

        br.close();
        pw.close();
    }
}
