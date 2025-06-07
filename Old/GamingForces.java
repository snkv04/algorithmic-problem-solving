import java.util.*;
import java.io.*;

public class GamingForces {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] h = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int count1s = 0;
            for (int health : h) if (health == 1) count1s++;

            int spells = count1s / 2;
            if (count1s % 2 != 0) spells += 1;
            spells += n - count1s;
            pw.println(spells);
        }

        br.close(); pw.close();
    }
}
