import java.util.*;
import java.io.*;

public class CirnosPerfectBitmasksClassroom {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            if ((n&1)>0) {
                if (n==1) {pw.println(3);continue;}
                else {pw.println(1);continue;}
            }
            for (int i = 1; i <= 30; i++) {
                if ((n&1<<i)>0) {
                    if (n==(1<<i)) {
                        pw.println((1<<i)+1);
                        break;
                    } else {
                        pw.println(1<<i);
                        break;
                    }
                }
            }
        }

        br.close(); pw.close();
    }
}
