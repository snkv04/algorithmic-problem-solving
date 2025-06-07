import java.util.*;
import java.io.*;

public class PetyaAndStrings {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String a = br.readLine().toLowerCase();
        String b = br.readLine().toLowerCase();
        pw.print(a.compareTo(b) == 0 ? 0 : a.compareTo(b) / Math.abs(a.compareTo(b)));

        br.close(); pw.close();
    }
}
