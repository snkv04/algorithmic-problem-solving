import java.util.*;
import java.io.*;

public class RatingSystem {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for ( ; t-->0; ) {
            // int n = Integer.parseInt(br.readLine());
            // int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            // long[] prefsum = new long[n+1];
            // for (int j = 1; j <= n; j++) {
            //     prefsum[j] = prefsum[j-1] + (long) a[j-1];
            // }

            // int negstart = -1;
            // long negsum = 0;
            // long maxneg = 0;
            // int maxnegstart = -1;
            // for (int j = 0; j <= n-1; j++) {
            //     if (a[j]<0) {
            //         if (negsum==0) {
            //             negstart = j;
            //             negsum += a[j];
            //         } else {
            //             negsum += a[j];
            //         }
            //     } else {
            //         if (negsum!=0) {
            //             if (negsum < maxneg) {
            //                 maxneg = negsum;
            //                 maxnegstart = negstart;
            //             }
            //             negsum = 0;
            //             negstart = -1;
            //         }
            //     }
            // }
            // if (negsum < maxneg) {
            //     maxneg = negsum;
            //     maxnegstart = negstart;
            //     negsum = 0;
            //     negstart = -1;
            // }
            // // pw.println(maxneg);
            // // pw.println(maxnegstart);
            // if (maxnegstart==-1) pw.println(Integer.MAX_VALUE);
            // else pw.println(prefsum[maxnegstart]);

            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            long[] prefsums = new long[n];
            prefsums[0] = a[0]; for (int i = 1; i <= n-1; i++) prefsums[i] = prefsums[i-1]+a[i];
            long currMin = a[n-1];
            long globalMin = a[n-1];
            long ans = a[n-1]<0?(n==1?0:prefsums[n-2]):((long)1e18);
            for (int i = n-2; i >= 0; i--) {
                currMin = Math.min(a[i], currMin+a[i]);
                if (currMin <= globalMin) {
                    globalMin = currMin;
                    ans = i==0?0:prefsums[i-1];
                }
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
