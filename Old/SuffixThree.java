import java.util.*;
import java.io.*;

public class SuffixThree {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        for (int i = 1; i <= n; i++) {
            String sentence = br.readLine();
            if (sentence.substring(sentence.length()-2).equals("po")) {
                pw.println("FILIPINO");
            } else if (sentence.substring(sentence.length()-4).equals("desu")
            || sentence.substring(sentence.length()-4).equals("masu")) {
                pw.println("JAPANESE");
            } else pw.println("KOREAN");
        }

        br.close(); pw.close();
    }
}
