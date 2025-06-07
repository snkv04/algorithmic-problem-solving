import java.util.*;
import java.io.*;

public class MysticPermutation {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (n==1) { pw.println(-1); continue; }
            TreeSet<Integer> unused = new TreeSet<Integer>();
            for (int i = 1; i <= n; i++) {
                unused.add(i);
            }
            for (int i = 0; i <= n-1; i++) {
                if (unused.size()==2 && unused.last()==p[n-1]) {
                    pw.print(unused.last() + " " + unused.first());
                    break;
                }
                int first = unused.pollFirst();
                if (first != p[i]) {
                    pw.print(first + " ");
                } else {
                    pw.print(unused.pollFirst() + " ");
                    unused.add(first);
                }
            }
            pw.println();
        }

        br.close(); pw.close();
    }
}
