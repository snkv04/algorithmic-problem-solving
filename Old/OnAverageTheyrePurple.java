import java.util.*;
import java.io.*;

public class OnAverageTheyrePurple {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        
        ArrayList<Integer>[] adjLists = new ArrayList[n];
        for (int i=0; i <= n-1; i++) adjLists[i] = new ArrayList<Integer>();
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0])-1;
            int b = Integer.parseInt(line[1])-1;
            adjLists[a].add(b);
            adjLists[b].add(a);
        }
        
        int[] dist = new int[n];
        boolean[] visited = new boolean[n];
        Arrays.fill(dist, Integer.MAX_VALUE/2); dist[0]=0;
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(Comparator.comparingInt(o -> dist[o]));
        pq.add(0);
        while (!pq.isEmpty()) {
            int node = pq.poll();
            if (visited[node]) continue;
            
            visited[node] = true;
            for (int next : adjLists[node]) {
                if (dist[node]+1 < dist[next]) {
                    dist[next] = dist[node]+1;
                    pq.add(next);
                }
            }
        }
        pw.println(dist[n-1]-1);
        
        br.close(); pw.close();
    }
}