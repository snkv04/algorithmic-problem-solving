import java.util.*;
import java.io.*;

public class ShoeShuffling {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            int[] s = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int last = 0;
            // O(2n) = O(n)
            int[] print = new int[n];
            boolean works = true;
            int i = 1;
            for ( ; i <= n-1; i++) {
                if (s[i] != s[last]) {
                    int len = i - last;
                    if (len == 1) {
                        works = false;
                        break;
                    } else {
                        for (int j = last; j <= i-2; j++) {
                            print[j] = j+2;
                        }
                        print[i-1]=last+1;
                        last = i;
                    }
                }
            }
            if (i-last == 1) {
                works = false;
            } else {
                for (int j = last; j <= i-2; j++) {
                    print[j] = j+2;
                }
                print[i-1]=last+1;
                last = i;
            }

            if (works) {
                for (int index = 0; index <= n-1; index++) {
                    pw.print(print[index] + " ");
                }
                pw.println();
            } else pw.println(-1);
        }

        br.close(); pw.close();
    }
}
