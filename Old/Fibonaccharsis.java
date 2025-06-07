import java.util.*;
import java.io.*;

public class Fibonaccharsis {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int ans = 0;
            for (int i = (n+1)/2; i <= n; i++) {
                int minus2 = n;
                int minus1 = i;
                boolean works = true;;
                pw.print("m2="+minus2+", m1="+minus1);
                for (int elements = 3; elements <= k; elements++) {
                    int curr = minus2 - minus1;
                    if (curr < 0 || curr > minus1) {
                        works = false;
                        break;
                    }
                    pw.print(", "+curr);
                    minus2 = minus1;
                    minus1 = curr;
                }
                ans += works?1:0;
                pw.println();
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
