import java.util.*;
import java.io.*;

public class PetyaAndSquare {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int len = Integer.parseInt(line[0]);
        int x = Integer.parseInt(line[1]);
        int y = Integer.parseInt(line[2]);
        int mid = len/2;
        if ((x==mid&&y==mid) || (x==mid&&y==mid+1) || (x==mid+1&&y==mid) || (x==mid+1&&y==mid+1)) {
            pw.print("NO");
        } else {
            pw.print("YES");
        }

        br.close(); pw.close();
    }
}
