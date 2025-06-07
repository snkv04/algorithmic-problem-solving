import java.util.*;
import java.io.*;

public class LoanRepayment {
    static long n, k, m;

    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("loan.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("loan.out")));

        String[] line = br.readLine().split(" ");
        n = Long.parseLong(line[0]);

        long lo = 1, hi = n, ans = -1;
        while (lo <= hi) {
            // System.out.println("here");
            n = Long.parseLong(line[0]); // repeated init every check bc prev implementation changed values during check
            k = Long.parseLong(line[1]);
            m = Long.parseLong(line[2]);
            long mid = (lo + hi) / 2;
            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        pw.println(ans);

        br.close(); pw.close();

        // binary search on the answer space. this is pretty evidenct since if a value of
        // x works, then all other values less than x would work, as they would make him
        // pay off his loan quicker; therefore, the answer space (the values of whether
        // or not x works) is monotonic.
        // to check a specific value of x, understand what happens for a certain value of
        // x. the amount that is paid off gets bigger and bigger, so N-G decreases, meaning
        // that Y decreases over time. it may eventually decrease to below m, but we can
        // consider that later. consider the different multiples of X that are below n and
        // the intervals formed between these multiples. the key realization is that if
        // N-G is in the same interval after a day passes, then Y stays the same. this is
        // true until N-G decreases below the multiple of X that it's above or equal to,
        // and then N-G continues decreasing but by one less each day (since the amount
        // it decreases each day is calculated by dividing by X, so the floor of (N-G)/X
        // will be one lower if N-G is in a lower interval from before.) so, we can jump
        // from interval to interval, counting how many days pass between each one (making
        // sure to do the math to account for the endpoints of the intervals) and
        // incrementing G by the number of days passed in that jump times Y for that
        // interval. there are two caveats, though. the first is that if the number of
        // days to reach the next endpoint of the interval is more than the number of days
        // left before doing k days, then the jump's length is just set to the remaining 
        // days and it is guaranteed that that is the last jump. the second one is that if
        // y is ever below m, then since y (or m) will never change for the rest of the
        // days, we can just instantly calculate if the amount paid over the remaining
        // days is sufficient (i.e. is more than or equal to n). also, after every jump,
        // within the loop at its end, we can check if n gallons of milk have been paid;
        // this way, we don't need a condition after the loop at the end of the method
        // and can just return false if we ever get to the point of leaving the loop.
    }

    static boolean check(long x) {
        // System.out.println("\nchecking "+x);
        long g = 0;
        long days = 0;
        for ( ; days < k; ) {
            long y = (n-g) / x;
            if (y < m) {
                return m * (k-days) >= n - g;
            }

            long jumpLength = (long)(((n-g) % x)/y) + 1;
            jumpLength = Math.min(jumpLength, k-days);
            g += jumpLength * y;
            days += jumpLength;

            if (g >= n) return true;
        }
        return false;
    }
}
