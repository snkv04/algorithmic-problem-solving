import java.util.*;
import java.io.*;

public class BinaryDeque {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int s = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            boolean found = false;
            int max = -1;
            int i = 0, j=0;
            int sum = a[0];
            while (i<=n-1 && j<=n-1) {
                if (sum < s) {
                    if (j==n-1) {
                        break;
                    }
                    j++;
                    sum += a[j];
                } else if (sum>s) {
                    sum -= a[i];
                    i++;
                } else {
                    found = true;
                    max = Math.max(max, j-i+1);
                    if (max==n) {
                        break;
                    }
                    j++;
                    if (j==n) break;
                    else sum += a[j];
                }
            }
            pw.println(found?(n-max):-1);
        }

        br.close(); pw.close();
    }
}
