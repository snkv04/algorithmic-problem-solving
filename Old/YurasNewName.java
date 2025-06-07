import java.util.*;
import java.io.*;

public class YurasNewName {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            char[] line = br.readLine().toCharArray();
            if (line.length == 1 && line[0] == '^') pw.println(1);
            else {
                int count = 0;
                for (int j = 0; j <= line.length - 1; j++) {
                    if (line[j] == '_') {
                        if (j == 0) count++;

                        // only checks the right of each _
                        if (j == line.length - 1 || line[j+1] == '_') count++;
                    }
                }
                pw.println(count);
            }
        }

        br.close(); pw.close();
    }
}
