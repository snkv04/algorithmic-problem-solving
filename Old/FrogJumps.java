import java.util.*;
import java.io.*;

public class FrogJumps {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i=1; i<=t; i++) {
            // char[] s=br.readLine().toCharArray();
            // boolean l = false;
            // int maxL = 0;
            // int lCount = 0;
            // for (int j = 0; j <= s.length-1; j++) {
            //     if (l) {
            //         if (s[j]=='L') lCount ++;
            //         else {
            //             maxL = Math.max(maxL, lCount);
            //             l=false;
            //         }
            //     } else {
            //         if (s[j]=='L') {
            //             l=true;
            //             lCount = 1;
            //         }
            //     }
            // }
            // maxL = Math.max(maxL, lCount);
            // pw.println(maxL+1);

            // alternatively, to find the (length of longest L streak + 1),
            // we can construct an array solely of Rs (including the start and
            // end points out of convenience given their purpose) and find the
            // max distance between any 2 Rs
            char[] s = br.readLine().toCharArray();
            ArrayList<Integer> Rs = new ArrayList();
            Rs.add(-1);
            for (int j = 0; j <= s.length-1; j++) {
                if (s[j]=='R') Rs.add(j);
            }
            Rs.add(s.length);
            int maxLength = 0;
            for (int j = 1; j <= Rs.size()-1; j++) {
                maxLength = Math.max(maxLength, Rs.get(j)-Rs.get(j-1));
            }
            pw.println(maxLength);
        }

        br.close(); pw.close();
    }
}
