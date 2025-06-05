import java.util.*;
import java.io.*;

public class BestSubsegment {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int max = -1;
        for (int i = 0; i <= n-1; i++) {
            max = Math.max(max, a[i]);
        }
        boolean last = false;
        int maxLength = 0, currLength = 0;
        for (int i = 0; i <= n-1; i++) {
            if (last) {
                if (a[i]==max) {
                    currLength++;
                } else {
                    last = false;
                    maxLength = Math.max(maxLength, currLength);
                }
            } else {
                if (a[i]==max) {
                    currLength = 1;
                    last = true;
                }
            }
        }
        maxLength = Math.max(maxLength, currLength);
        pw.println(maxLength);
        

        br.close(); pw.close();
    }
}
