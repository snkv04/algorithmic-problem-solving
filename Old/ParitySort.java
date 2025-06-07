import java.util.*;
import java.io.*;

public class ParitySort {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        
        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            PriorityQueue<Integer> even = new PriorityQueue<Integer>(), odd = new PriorityQueue<Integer>();
            for (int i = 0; i <= n-1; i++) {
                if (a[i]%2 == 0) even.add(a[i]);
                else odd.add(a[i]);
            }
            
            for (int i = 0; i <= n-1; i++)
                if (a[i]%2==0) a[i] = even.poll();
                else a[i] = odd.poll();
                
            boolean works = true;
            for (int i = 1; i <= n-1; i++)
                if (a[i] < a[i-1]) { works = false; break; }
            pw.println(works?"YES":"NO");
        }
        
        br.close(); pw.close();
    }
}