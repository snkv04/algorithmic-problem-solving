import java.util.*;
import java.io.*;

public class NumberOfPairs {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int l = Integer.parseInt(line[1]);
            int r = Integer.parseInt(line[2]);
            int[] input = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            Integer[] a = new Integer[n];
            for (int i = 0; i <= n-1; i++) a[i] = input[i];
            Arrays.sort(a);

            long ans = 0;
            for (int i = 0; i <= n-1; i++) {
                int leftInd = -1, rightInd = -1;
                int low = 0, high = n-1;
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (a[mid] >= l-a[i]) {
                        leftInd = mid;
                        high = mid-1;
                    } else {
                        low = mid+1;
                    }
                }
                low=0; high=n-1;
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (a[mid] <= r-a[i]) {
                        rightInd = mid;
                        low = mid+1;
                    } else {
                        high = mid-1;
                    }
                }

                if (leftInd != -1) {
                    ans += rightInd - leftInd + 1;
                    if (i >= leftInd && i <= rightInd) ans--;
                }
            }
            pw.println(ans/2);
        }

        br.close(); pw.close();
    }
}
