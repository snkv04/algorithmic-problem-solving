import java.util.*;
import java.io.*;

public class TeamOlympiad {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        TreeSet<Integer> p = new TreeSet<Integer>();
        TreeSet<Integer> m = new TreeSet<Integer>();
        TreeSet<Integer> pe = new TreeSet<Integer>();
        for (int i = 0; i <= n-1; i++) {
            if (a[i]==1) p.add(i+1);
            else if (a[i]==2) m.add(i+1);
            else pe.add(i+1);
        }
        int max = Math.min(p.size(), Math.min(m.size(), pe.size()));
        pw.println(max);
        for (int i = 1; i <= max; i++) {
            pw.print(p.pollFirst()+" ");
            pw.print(m.pollFirst()+" ");
            pw.println(pe.pollFirst()+" ");
        }

        br.close(); pw.close();
    }
}
