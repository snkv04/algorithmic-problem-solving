import java.util.*;
import java.io.*;

public class TrackingSegments {
    static int n, m, q;
    static int[][] segments;
    static int[] xs;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            n = Integer.parseInt(line[0]);
            m = Integer.parseInt(line[1]);
            segments = new int[m][2];
            for (int i = 0; i <= m-1; i++) {
                segments[i] = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
                // line = br.readLine().split(" ");
                // segments[i] = new int[2];
                // segments[i][0] = Integer.parseInt(line[0])-1;
                // segments[i][1] = Integer.parseInt(line[1])-1;
            }
            q = Integer.parseInt(br.readLine());
            xs = new int[q+1];
            for (int i = 1; i <= q; i++) {
                xs[i] = Integer.parseInt(br.readLine()) - 1;
            }

            int low = 1, high = q, ans = -1;
            // it is not possible for the answer to be 0, because none of the segments
            // will be "beautiful" (having more 1s than 0s) if 0 changes have been made
            // to alter any of the elements of the array
            while (low <= high) {
                int mid = (low + high) / 2;
                // System.out.println("testing "+mid);
                if (check(mid)) {
                    high = mid-1;
                    ans = mid;
                } else {
                    low = mid+1;
                }
            }
            // for (int i = 1; i <= q; i++) System.out.println("i="+i+", and check(i)="+check(i));
            // System.out.println(check(3));
            pw.println(ans);
        }

        br.close(); pw.close();
    }

    static boolean check(int changes) {
        int[] arr = new int[n];
        for (int i = 1; i <= changes; i++) {
            arr[xs[i]] = 1;
        }
        // System.out.println("so the array looks like this: "+Arrays.toString(arr));
        int[] prefsums = new int[n+1];
        for (int i = 1; i <= n; i++) {
            prefsums[i] = prefsums[i-1] + arr[i-1];
        }
        // System.out.println("and the prefix sums look like this: "+Arrays.toString(prefsums));

        // boolean works = false;
        for (int i = 0; i <= m-1; i++) {
            int left = segments[i][0];
            int right = segments[i][1];
            int length = right-left+1;
            // System.out.println("current segment: l="+left+",r="+right);
            int threshold = length / 2 + 1;
            if (prefsums[right] - prefsums[left-1] >= threshold) return true;
        }
        return false;
    }
}
