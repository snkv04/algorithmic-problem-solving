import java.util.*;
import java.io.*;

public class MusicalPuzzle {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            String melody = br.readLine();
            HashSet<String> notes = new HashSet<String>();
            for (int j = 0; j <= n-2; j++) {
                notes.add(melody.substring(j, j+2));
            }
            pw.println(notes.size());
        }

        br.close(); pw.close();
    }
}
