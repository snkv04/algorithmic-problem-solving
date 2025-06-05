import java.util.*;
import java.io.*;

public class BovineShuffle {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader("shuffle.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("shuffle.out")));
        int n = Integer.parseInt(br.readLine());
        int[] shuffle = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] cows = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] unshuffled = new int[n];
        for(int j = 1; j <= 3; j++) {
            for(int i = 0; i <= n-1; i++) {
                // int a = shuffle[i];
                // int oldPos = i;
                // int newPos = shuffle[i];
                // shuffledCows[a - 1] = unshuffledCows[i]

                unshuffled[i] = cows[shuffle[i] - 1];
            }
            cows = Arrays.copyOf(unshuffled, n);
        }

        for(int i = 0; i <= n-1; i++) {
            pw.println(unshuffled[i]);
        }

        br.close();
        pw.close();
    }
}
