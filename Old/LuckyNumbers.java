import java.util.*;
import java.io.*;

public class LuckyNumbers {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for(int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int l = Integer.parseInt(line[0]);
            int r = Integer.parseInt(line[1]);
            int answer = l;
            for (int j = l; j <= Math.min(l+100, r); j++) {
                if (j % 100 == 90) {
                    answer = j;
                    break;
                }
                
                if (dist(j) > dist(answer)) answer=j;
            }
            pw.println(answer);
        }

        br.close(); pw.close();
    }

    static int dist(int a) {
        if (a==0) return 0;

        int min=Integer.MAX_VALUE, max=Integer.MIN_VALUE;
        while (a > 0) {
            int digit = a % 10;
            a /= 10;
            min=Math.min(min, digit);
            max=Math.max(max, digit);
        }
        return max-min;
    }
}
