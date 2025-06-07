import java.util.*;
import java.io.*;

public class KefaAndPark {
    static ArrayList<Integer>[] adjLists;
    static boolean[] visited;
    static int[] numCats;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        adjLists = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adjLists[i] = new ArrayList();
        }
        for (int i =0; i <= n-2; i++) {
            line = br.readLine().split(" ");
            int one = Integer.parseInt(line[0]) - 1;
            int two = Integer.parseInt(line[1]) - 1;
            adjLists[one].add(two);
            adjLists[two].add(one);
        }
        numCats = new int[n];

        Stack<Integer> s = new Stack<Integer>();
        s.add(0);
        numCats[0] = a[0];
        visited = new boolean[n];
        while (!s.isEmpty()) {
            int node = s.pop();
            visited[node] = true;
            for (int next : adjLists[node]) {
                if (!visited[next]) {
                    numCats[next] = a[next]==0?0:numCats[node]+1;
                    if (numCats[next] <= m) s.add(next);
                }
            }
        }
        // pw.println(Arrays.toString(a));
        // pw.println(Arrays.toString(numCats));
        // pw.println(Arrays.toString(visited));

        int ans = 0;
        for (int i = 1; i <= n-1; i++) {
            if (adjLists[i].size()==1 && visited[i]) ans++;
        }
        pw.print(ans);

        br.close(); pw.close();
    }

    // // // //

    static class Multiset {
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }
}
