import java.util.*;
import java.io.*;

public class MaxAndMex {
    static int n;
    static int[] a;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            Arrays.sort(a);
            int mex = -1;
            if (a[0] != 0) mex = 0;
            else {
                for (int j = 0; j <= n-1; j++) {
                    if (j==n-1) {
                        mex = a[n-1]+1;
                    } else {
                        if (a[j+1] != a[j]+1) {
                            mex = a[j]+1;
                            break;
                        }
                    }
                }
            }

            if (mex > a[n-1]) pw.println(n+k);
            else {
                int adding = (mex + a[n-1] + 1)/2;
                if (contains(adding)) pw.println(n);
                else pw.println(n+Math.min(1, k));
            }
        }

        br.close(); pw.close();
    }

    static boolean contains(int adding) {
        int lo=0, hi=n-1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            // if (a[mid] > adding) lo = mid+1;
            // else if (a[mid] < adding) hi = mid-1;
            if (a[mid] > adding) hi = mid-1;
            else if (a[mid] < adding) lo = mid+1;
            else return true;
        }
        return false;
    }
}