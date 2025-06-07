import java.util.*;
import java.io.*;

public class SumOfSubstrings {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            char[] s = br.readLine().toCharArray();
            int count = 0, first1 = -1, last1 = -1;
            for (int i = 0; i <= n-1; i++) {
                if (s[i]=='1') {
                    if (count==0) first1 = i;
                    count++;
                    last1 = i;
                }
            }

            if (count==0) {
                pw.println(0);
                continue;
            } else if (count==1) {
                if (n-1-last1 <= k) {
                    pw.println(1);
                } else if (first1 <= k) {
                    pw.println(10);
                } else {
                    pw.println(11);
                }
                continue;
            }

            int sum = 0;
            if (/* count > 0 && */ n-1-last1 <= k) {
                sum = 1;
                k -= n-1-last1;
            } else {
                sum = 11;
            }

            if (/* count > 1 && */ first1 <= k) {
                sum += 10;
            } else {
                sum += 11;
            }

            sum += 11 * (count-2);
            pw.println(sum);
        }

        br.close(); pw.close();

        // the only possible numbers that can be made for each i in {1, ..., n-1} are 0, 1, 10, and 11.
        // if we go from left to right, looking at all the windows of size 2, then it is clear that
        // each 1 is in two windows, and in the left window is a 01 or 11 if there is a 0 or 1 to the left,
        // respectively, and in the right window is a 10 or 11 if there is a 0 or 1 to the right,
        // respectively. however, it can be further observed that regardless, if we view every single
        // character independently, then all 1s "contribute" a 01 to the left and a 10 to the right,
        // so 11 in total, and then these get added up appropriately depending on if there is a 1 directly
        // to the left or right. the only exceptions are a 1 being at the start or end of the string, in
        // which situation that one would contribute a 10 or 1, respectively. other than these exceptions,
        // moving around the middle 1s does nothing. so, we simply try to move the ones that are closest
        // to the ends to the ends, prioritizing moving the end 1 to the end of the binary string.
    }
}
