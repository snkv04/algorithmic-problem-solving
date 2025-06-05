import java.util.*;
import java.io.*;

public class BuyAShovel {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int k = Integer.parseInt(line[0]);
        int r = Integer.parseInt(line[1]);
        int ans = -1;
        for (int i = 1; i <= 9; i++) {
            if ((i*k)%10==r || (i*k)%10==0) {
                ans = i;
                break;
            }
        }
        pw.print(ans);

        br.close(); pw.close();
    }
}
