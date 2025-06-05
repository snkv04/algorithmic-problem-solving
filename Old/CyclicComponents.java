import java.util.*;
import java.io.*;

public class CyclicComponents {
    static ArrayList<Integer>[] adjLists;
    static boolean visited[];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        adjLists = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) adjLists[i] = new ArrayList<>();
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0])-1;
            int b = Integer.parseInt(line[1])-1;
            adjLists[a].add(b);
            adjLists[b].add(a);
        }

        visited = new boolean[n];
        int count = 0;
        for (int i = 0; i<=n-1; i++) {
            if (!visited[i]) {
                boolean works = true;
                Stack<Integer> s = new Stack();
                s.add(i);
                while (!s.isEmpty()) {
                    int node = s.pop();
                    visited[node] = true;
                    if (adjLists[node].size() != 2) works = false;
                    for (int next : adjLists[node]) {
                        if (!visited[next]) s.add(next);
                    }
                }
                count += works?1:0;
            }
        }
        pw.println(count);

        br.close(); pw.close();
    }
}
