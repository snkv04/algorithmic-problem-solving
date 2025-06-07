import java.util.*;
import java.io.*;

public class MoreCowbell {
    static int n, k;
    static int[] cowbells;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        k = Integer.parseInt(line[1]);
        cowbells = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int left=0, right=1050000000, ans=-1;
        while (left <= right) {
            int mid = (left+right)/2;
            if (check(mid)) {
                ans=mid;
                right = mid-1;
            } else {
                left = mid+1;
            }
        }
        pw.println(ans);

        br.close(); pw.close();
    }

    static boolean check(int size) {
        if (size < cowbells[n-1]) return false;

        int left=0, right=n-1;
        for (int i = 0; i <= k-1 && left<=right; i++) {
            if (size >= cowbells[right] + cowbells[left]) {
                right--;
                left++;
            } else right--;
        }
        return left>right;
    }
}
