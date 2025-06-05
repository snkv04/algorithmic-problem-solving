import java.util.*;
import java.io.*;

public class CountingLiars {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        char[] dirs = new char[n];
        int[] p = new int[n];
        int[] sorted = new int[n+2];
        for (int i = 0; i <= n-1; i++) {
            dirs[i] = sc.next().charAt(0);
            int num = sc.nextInt();
            p[i] = num;
            sorted[i]=num;
        }
        sorted[n] = -10;
        sorted[n+1] = 2000000000;
        Arrays.sort(sorted);
        int max = 0;
        for (int i = 0; i <= n; i++) {
            int left = sorted[i];
            int right = sorted[i+1];
            int count = 0;
            for (int j = 0; j <= n-1; j++) {
                if (p[j] >= right && dirs[j] == 'L' || p[j] <= left && dirs[j]=='G') {
                    count++;
                }
            }
            max = Math.max(count, max);
        }
        pw.println(n-max);

        sc.close(); pw.close();

        // my first attempt at an answer was to loop through each cow, and for that
        // cow, assume that its interval of position information is true and then
        // see how many other cows agree with that by another for loop. the problem
        // with this approach is that two other cows may agree with the current cow
        // but not with each other, and this solution doesn't account for this possibility.
        // i ended up coming up with the solution of checking how many cows agree with each
        // possible interval, where the endpoints of the intervals are the positions
        // that the cows say bessie might be at. having the endpoints be anywhere else
        // than these positions is unnecessary, as they are the only points on the number
        // line where the number of cows that agree with a specific point can change.
    }
}
