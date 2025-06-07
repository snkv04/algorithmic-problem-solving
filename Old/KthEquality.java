import java.util.*;
import java.io.*;

public class KthEquality {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int A = Integer.parseInt(line[0]);
            int B = Integer.parseInt(line[1]);
            int C = Integer.parseInt(line[2]);
            long k = Long.parseLong(line[3]);
            int a = (int) Math.pow(10, A-1);
            long maxa = (long) Math.pow(10, A)-1;
            long minc = (long) Math.pow(10, C-1);
            long maxc = (long) Math.pow(10, C) - 1;
            while (a <= maxa) {
                long minb = Math.max((long) Math.pow(10, B-1), minc - a);
                long maxb = Math.min((long) Math.pow(10, B)-1, maxc-a);
                if (a + minb > maxc) {
                    pw.println(-1);
                    break;
                }
                long numbs = Math.min(maxc - a, maxb-minb+1);
                if (numbs <= 0) {
                    a++; continue;
                }
                if (k <= numbs) {
                    k--;
                    minb += k;
                    pw.println(a + " + " + minb + " = " + (a+minb));
                    break;
                } else {
                    k-=numbs;
                    a++;
                }
            }
            if (a > maxa) pw.println(-1);
        }

        br.close(); pw.close();

        // we want to find the kth equation a+b=c such that a has A digits and so on.
        // we can iterate through all the values of a, checking how many values of b
        // work with this value of a. (although i said i wouldn't do this, i'm not typing
        // out all the math for the mins and maxes as i'm getting lazy; the math is given
        // above.) if the value of k at the current value of a is more than the amount
        // of possible b values there are, signifying that the desired equation cannot be
        // reached with the current value of a, then a is incremented by 1 and k is
        // decremented by the number of possible b values ("jumping" to the next a value).
        // we keep moving a up until k is within the number of b values for the current
        // value of a. then, we identify what the appropriate value of b is (accounting
        // for how if k=1 then we use the minimum value of b and not the next one) and
        // print out the equation. if we go through all possible values of a and we
        // still haven't reached the kth equation, then k is too high for the given
        // A, B, and C, and so it is not possible. additionally, if C is less than
        // either A or B then it is also manifestly not possible. also, if a certain
        // value of a has no possible b values (shown above if "numbs" is less than
        // or equal to 0), then a is incremented and the loop continues to the next
        // iteration.
    }
}
