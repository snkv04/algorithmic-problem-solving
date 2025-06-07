import java.util.*;
import java.io.*;

public class Drought {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int test = 1; test <= t; test++) {
            int n = Integer.parseInt(br.readLine());
            int[] h = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

            if (n==1) {
                pw.println(0);
                continue;
            } else if (n==2) {
                pw.println(h[0]==h[1]?0:-1);
                continue;
            }

            long count = 0;
            for (int i = 1; i <= n-2 && count >= 0; i++) {
                if (h[i-1] < h[i]) {
                    long change = h[i]-h[i-1];
                    count += 2*change;
                    h[i] -= change;
                    h[i+1] -= change;
                    if (h[i+1] < 0) count=-1;
                }
            }
            // pw.println(Arrays.toString(h));

            for (int i = n-2; i >= 1 && count>=0; i--) {
                if (h[i+1] < h[i]) {
                    long change = h[i]-h[i+1];
                    count += 2*change;
                    h[i] -= change;
                    h[i-1] -= change;
                    if (h[i-1] < 0) count=-1;
                }
            }
            // pw.println(Arrays.toString(h));

            pw.println(h[0] > h[1] ? -1 : count);
        }

        br.close(); pw.close();

        // do a pass from the left to the right, making the whole array non-increasing.
        // do a pass from right to left, making the whole array equal. if at any point
        // the change is too much, print -1. if at the very end, the first element is still
        // greater than the second, print -1. else print the number of bags of corn required.
        // 
        // how exactly do you come up with a solution like this?
        // well, equalizing an array is much easier if it is sorted in non-decreasing or
        // non-increasing order. the array starts off lumpy (if all the hungers are drawn out
        // as bars), so the first pass can ensure that it is "sorted", making the second pass
        // easier. still, it's difficult to come up with this solution. it may help to first
        // consider a best case example to figure out how the algorithm should work, and then
        // use edge cases to see if it works and/or refine it to cover everything.
    }
}
