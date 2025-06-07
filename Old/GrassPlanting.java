import java.util.*;
import java.io.*;

public class GrassPlanting {
    // static ArrayList<Integer>[] adj;

    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("planting.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("planting.out")));

        // int n = Integer.parseInt(br.readLine());
        // adj = new ArrayList[n];
        // for (int i = 0; i <= n-1; i++) {
        //     adj[i] = new ArrayList<>();
        // }
        // for (int i = 1; i <= n-1; i++) {
        //     String[] line = br.readLine().split(" ");
        //     int a = Integer.parseInt(line[0])-1;
        //     int b = Integer.parseInt(line[1])-1;
        //     adj[a].add(b);
        //     adj[b].add(a);
        // }

        // int maxDegree = 0;
        // for (int i = 0; i <= n-1; i++) {
        //     maxDegree = Math.max(maxDegree, adj[i].size());
        // }
        // pw.println(maxDegree+1);

        int n = Integer.parseInt(br.readLine());
        int[] numAdjacent = new int[n];
        for (int i = 1; i <= n-1; i++) {
            String[] line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0])-1;
            int b = Integer.parseInt(line[1])-1;
            numAdjacent[a]++;
            numAdjacent[b]++;
        }
        int maxDegree = 0;
        for (int i = 0; i <= n-1; i++) maxDegree = Math.max(maxDegree, numAdjacent[i]);
        pw.println(maxDegree+1);

        br.close(); pw.close();
    }
}
