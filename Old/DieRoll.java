import java.util.*;
import java.io.*;

public class DieRoll {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int y = Integer.parseInt(line[0]);
        int w = Integer.parseInt(line[1]);
        int d = 6-Math.max(y,w)+1;
        int num = d / gcd(6,d);
        int denom = 6/gcd(6,d);
        pw.println(num+"/"+denom);

        br.close(); pw.close();
    }

    static int gcd(int a, int b) {
        if (b==0) return a;
        else return gcd(b, a%b);
    }
}
