import java.util.*;
import java.io.*;

public class HQ9Plus {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        char[] program = br.readLine().toCharArray();
        boolean works = false;
        for (int character : program) {
            if (character=='H'||character=='Q'||character=='9') {
                works = true;
                break;
            }
        }
        pw.print(works?"YES":"NO");

        br.close(); pw.close();
    }
}
