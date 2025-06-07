import java.util.*;
import java.io.*;

public class GrabTheCandies {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int m=0, b=0;
            for (int num : a) if (num%2==0) m+=num; else b+=num;
            pw.println(m>b?"YES":"NO");
        }

        br.close(); pw.close();
    }
}
