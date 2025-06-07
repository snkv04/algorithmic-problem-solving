import java.util.*;
import java.io.*;

public class ReverseBinaryStrings {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            char[] binaryString = br.readLine().toCharArray();
            int count = 0;
            for (int j = 1; j <= n-1; j++) {
                // if (binaryString[j] == '1' && binaryString[j-1] == '1') count++;
                if (binaryString[j] == binaryString[j-1]) count++;
            }
            pw.println((count + 1)/ 2);
        }

        br.close(); pw.close();
    }
}
