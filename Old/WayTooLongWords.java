import java.util.*;
import java.io.*;

public class WayTooLongWords {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        for (int i = 1; i <= n; i++) {
            char[] word = br.readLine().toCharArray();
            if (word.length <= 10) {
                pw.println(word);
            } else {
                pw.println(word[0] + "" + (word.length-2) + "" + word[word.length-1]);
            }
        }

        br.close(); pw.close();
    }
}
