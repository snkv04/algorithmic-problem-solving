import java.util.*;
import java.io.*;

public class TenzingAndBooks {
    static int n, x;
    static Queue<Integer> a, b, c;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int x = Integer.parseInt(line[1]);
            a = new LinkedList<Integer>();
            line = br.readLine().split(" ");
            for (int j = 0;j<=n-1;j++) {
                a.add(Integer.parseInt(line[j]));
            }
            b = new LinkedList<Integer>();
            line = br.readLine().split(" ");
            for (int j = 0;j<=n-1;j++) {
                b.add(Integer.parseInt(line[j]));
            }
            c = new LinkedList<Integer>();
            line = br.readLine().split(" ");
            for (int j = 0;j<=n-1;j++) {
                c.add(Integer.parseInt(line[j]));
            }

            int knowledge = 0;
            boolean done = false;
            boolean topworks = true;
            for (int j=1;j<=n && topworks && !done;j++) {
                int topA = a.poll();
                for (int k=0;k<=30;k++) {
                    if ((1<<k&x)==0 && (1<<k & topA)>0) {
                        topworks=false;
                        break;
                    }
                }
                if (topworks) { knowledge = knowledge | topA; }
                if (knowledge == x) {done=true;break;}
            }
            topworks=true;
            for (int j=1;j<=n && topworks && !done;j++) {
                int topB = b.poll();
                for (int k=0;k<=30;k++) {
                    if ((1<<k&x)==0 && (1<<k & topB)>0) {
                        topworks=false;
                        break;
                    }
                }
                if (topworks) { knowledge = knowledge | topB; }
                if (knowledge == x) {done=true;break;}
            }
            topworks = true;
            for (int j=1;j<=n && topworks && !done;j++) {
                int topC = c.poll();
                for (int k=0;k<=30;k++) {
                    if ((1<<k&x)==0 && (1<<k & topC)>0) {
                        topworks=false;
                        break;
                    }
                }
                if (topworks) { knowledge = knowledge | topC; }
                if (knowledge == x) {done=true;break;}
            }

            if (done) pw.println("Yes");
            else pw.println("No");
        }

        br.close(); pw.close();
    }
}
