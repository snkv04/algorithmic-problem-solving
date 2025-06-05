import java.util.*;
import java.io.*;

public class CopilCopacDrawsTrees {
    static ArrayList<Pair>[] adjLists;
    // static int[] step;
    static boolean visited[];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            adjLists = new ArrayList[n];
            for (int i = 0; i <= n-1; i++) {
                adjLists[i] = new ArrayList<>();
            }
            // step = new int[n];

            // step[0] = 0;
            for (int i = 1; i <= n-1; i++) {
                String[] line = br.readLine().split(" ");
                int a = Integer.parseInt(line[0]) - 1;
                int b = Integer.parseInt(line[1]) - 1;
                adjLists[a].add(new Pair(b, i));
                adjLists[b].add(new Pair(a, i));
                // step[b] = i;
            }

            int[] readings = new int[n];
            readings[0] = 1;
            Stack<Pair> s = new Stack<Pair>();
            s.add(new Pair(0, 0));
            visited = new boolean[n];
            while (!s.isEmpty()) {
                Pair node = s.pop();
                visited[node.num] = true;
                for (Pair next : adjLists[node.num]) {
                    if (!visited[next.num]) {
                        readings[next.num] = next.edgeStep>node.edgeStep ? readings[node.num] : readings[node.num]+1;
                        s.add(next);
                    }
                }
            }

            int ans = 0;
            for (int numReadings : readings) ans = Math.max(ans, numReadings);
            pw.println(ans);
        }

        br.close(); pw.close();
    }

    static class Pair {
        int num, edgeStep;

        public Pair(int num, int step) {
            this.num = num;
            this.edgeStep = step;
        }
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
