import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class BowsersPipes {
    static BufferedReader br;
    static PrintWriter pw;
    static int[] finalDest;
    static ArrayList<Integer>[] reverse;
    static int[] a;
    static TreeSet<Pair>[] pipes;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        finalDest = new int[n]; Arrays.fill(finalDest, -1);
        reverse = new ArrayList[n]; for (int i = 0; i < n; i++) reverse[i] = new ArrayList<>();
        a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] out = new int[n];
        for (int i = 0; i < n; i++) {
            dfs(i);
            if (a[i] != -1) {
                out[i]++;
                reverse[a[i]].add(i);
            }
        }

        pipes = new TreeSet[n]; for (int i = 0; i < n; i++) pipes[i] = new TreeSet<>();
        for (int i = 0; i < n; i++) {
            if (out[i] == 0) {
                dfs2(i, 0, i);
            }
        }

        int A = Integer.parseInt(br.readLine());
        a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        for (int ai : a) {
            pw.println(pipes[finalDest[ai]].first().a);
        }
    }

    static int dfs(int curr) {
        if (finalDest[curr] != -1) {
            return finalDest[curr];
        } else if (a[curr] == -1) {
            finalDest[curr] = curr;
        } else {
            finalDest[curr] = dfs(a[curr]);
        }
        return finalDest[curr];
    }

    static void dfs2(int node, int dist, int start) {
        int count = 0;
        for (int next : reverse[node]) {
            dfs2(next, dist+1, start);
            count++;
        }
        if (count == 0) {
            pipes[start].add(new Pair(node, dist));
        }
    }

    static class Pair implements Comparable<Pair> {
        int a, b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
        
        @Override
        public boolean equals(Object obj) {
            if (this == obj) return true;
            if (obj == null) return false;
            if (!(obj instanceof Pair)) return false;

            Pair other = (Pair) obj;
            return this.a == other.a && this.b == other.b;
        }

        @Override
        public int hashCode() {
            return (this.a+" "+this.b).hashCode();
        }

        public int compareTo(Pair other) {
            if (this.b != other.b) return this.b - other.b;
            else return this.a - other.a;
        }
    }
}
