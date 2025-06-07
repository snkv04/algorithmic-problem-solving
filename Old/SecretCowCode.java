import java.util.*;
import java.io.*;

public class SecretCowCode {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("cowcode.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cowcode.out")));

        String[] line = br.readLine().split(" ");
        String word = line[0];
        long n = Long.parseLong(line[1]);
        if (n <= word.length()) {
            pw.println(word.substring((int)(n-1), (int)(n)));
        } else {
            TreeSet<Long> doubles = new TreeSet();
            long val = word.length();
            while (val <= n) {
                doubles.add(val);
                val *= 2;
            }

            while (n > word.length()) {
                long lower = doubles.lower(n);
                if (n == lower+1) n--;
                // long numLayersSkipped = log()
                else n -= lower + 1;
            }
            if (n <= 0) {
                pw.println(word.substring((int)(word.length()+n-1), (int)(word.length()+n)));
            } else {
                pw.println(word.substring((int)(n-1), (int)n));
            }
        }

        // let's gooo

        br.close(); pw.close();
    }
}
