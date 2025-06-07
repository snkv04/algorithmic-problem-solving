import java.util.*;
import java.io.*;

public class SubwayTreeSystem {
    static BufferedReader br;
    static PrintWriter pw;
    static ArrayList<Integer>[] adj1, adj2;
    static char[] first, second;
    static int count, index, n;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        first = br.readLine().toCharArray();
        second = br.readLine().toCharArray();
        if (first.length != second.length) {
            pw.println("different");
            return;
        }

        n = first.length / 2;
        if (n == 0) {
            pw.println("same");
            return;
        }

        adj1 = new ArrayList[n+1];
        for (int i = 0; i <= n; i++) adj1[i] = new ArrayList<>();
        count = 0;
        index = 0;
        dfs(1, 0);
        adj2 = new ArrayList[n+1];
        for (int i = 0; i <= n; i++) adj2[i] = new ArrayList<>();
        count = 0;
        index = 0;
        dfs(2, 0);

        pw.println(dfs2(1, 0).equals(dfs2(2, 0))?"same":"different");
    }

    static void dfs(int whichTree, int node) {
        if (whichTree == 1) {
            boolean loop = first[index] == '0';
            while (loop) {
                count++;
                adj1[node].add(count);
                index++;
                dfs(whichTree, count);
                loop = index <= 2*n-1 && first[index] == '0';
            }
            if (index <= 2*n-1 && first[index] == '1') {
                index++;
            }
        } else {
            boolean loop = second[index] == '0';
            while (loop) {
                count++;
                adj2[node].add(count);
                index++;
                dfs(whichTree, count);
                loop = index <= 2*n-1 && second[index] == '0';
            }
            if (index <= 2*n-1 && second[index] == '1') {
                index++;
            }
        }
    }

    static String dfs2(int whichTree, int node) {
        if (whichTree == 1) {
            StringBuilder sb = new StringBuilder("(");
            ArrayList<String> subtrees = new ArrayList<>();
            for (int next : adj1[node]) {
                subtrees.add(dfs2(whichTree, next));
            }
            Collections.sort(subtrees);
            for (String subtree : subtrees) sb.append(subtree);
            sb.append(")");
            return sb.toString();
        } else {
            StringBuilder sb = new StringBuilder("(");
            ArrayList<String> subtrees = new ArrayList<>();
            for (int next : adj2[node]) {
                subtrees.add(dfs2(whichTree, next));
            }
            Collections.sort(subtrees);
            for (String subtree : subtrees) sb.append(subtree);
            sb.append(")");
            return sb.toString();
        }
    }
}
