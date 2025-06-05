import java.util.*;
import java.io.*;

public class BreedCounting {
    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("bcount.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("bcount.out")));

        String[] line = br.readLine().split(" ");
        int N = Integer.parseInt(line[0]);
        int Q = Integer.parseInt(line[1]);
        int[] prefixH = new int[N+1];
        int[] prefixG = new int[N+1];
        int[] prefixJ = new int[N+1];
        prefixH[0] = 0; prefixG[0] = 0; prefixJ[0] = 0;
        for (int i = 1; i <= N; i++) {
            int breed = Integer.parseInt(br.readLine());
            prefixH[i] = prefixH[i-1];
            prefixG[i] = prefixG[i-1];
            prefixJ[i] = prefixJ[i-1];
            if (breed == 1) prefixH[i]++;
            else if (breed == 2) prefixG[i]++;
            else prefixJ[i]++;
        }

        for (int i = 1; i <= Q; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            pw.print(prefixH[b]-prefixH[a-1] + " ");
            pw.print(prefixG[b]-prefixG[a-1] + " ");
            pw.print(prefixJ[b]-prefixJ[a-1]);
            pw.println();
        }

        br.close(); pw.close();
    }
}
