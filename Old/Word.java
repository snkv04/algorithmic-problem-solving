import java.util.*;
import java.io.*;

public class Word {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String s = br.readLine();
        String sLower = s.toLowerCase();
        int lower = 0, upper = 0;
        for (int i = 0; i <= s.length()-1; i++) {
            if (s.substring(i, i+1).equals(sLower.substring(i,i+1))) {
                lower++;
            } else upper++;
        }
        if (s.length()-lower > s.length()-upper) {
            pw.println(s.toUpperCase());
        }
        else pw.println(sLower);

        br.close(); pw.close();
    }
}
