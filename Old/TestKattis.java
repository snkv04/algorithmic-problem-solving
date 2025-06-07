// import java.util.*;
// import java.io.*;

// public class TestKattis {
//     static int MOD = (int) (1e9 + 7); // 998244353
//     static int index;
//     static ArrayList<Integer>[] adjLists;
//     static boolean[] visited;
//     static int[] id, low;
//     static boolean[] used, onStack;
//     static Stack<Integer> stack;
//     static int counter;
//     static TreeSet<TreeSet<Character>> components;

//     public static void main(String[] args) throws IOException {
//         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//         PrintWriter pw = new PrintWriter(System.out);

//         while (true) {
//             int n = Integer.parseInt(br.readLine());
//             if (n == 0) break;

//             index = 0;
//             used = new boolean[26];
//             adjLists = new ArrayList[26]; for (int i = 0; i <= 25; i++) adjLists[i] = new ArrayList<>();
//             for (int i = 1; i <= n; i++) {
//                 String[] line = br.readLine().split(" ");
//                 int best = line[5].charAt(0) - 'A';
//                 for (int j = 0; j <= 4; j++) {
//                     int other = line[j].charAt(0)-'A';
//                     if (other != best) {
//                         adjLists[best].add(other);
//                         used[best] = true; used[other] = true;
//                     }
//                 }
//             }

//             // Tarjan's
//             visited = new boolean[26];
//             id = new int[26]; low = new int[26];
//             stack = new Stack<>();
//             onStack = new boolean[26];
//             counter = 0;
//             components = new TreeSet<TreeSet<Character>>(Comparator.comparingInt(o -> (int)o.first()));
//             for (int i = 0; i <= 25; i++) {
//                 if (used[i] && !visited[i]) dfs(i);
//             }
            
//             for (TreeSet<Character> component : components) {
//                 for (char c : component) pw.print(c + " ");
//                 pw.println();
//             }

//             pw.println();
//         }
//         br.close(); pw.close();
//     }

//     static void dfs(int node) {
//         visited[node] = true;
//         stack.add(node); onStack[node] = true;
//         id[node] = low[node] = counter;
//         counter++;

//         for (int next : adjLists[node]) {
//             if (!visited[next])
//                 dfs(next);
//             if (onStack[next])
//                 low[node] = Math.min(low[node], low[next]);
//         }

//         if (id[node] == low[node]) {
//             TreeSet<Character> component = new TreeSet<>();
//             while (true) {
//                 int popped = stack.pop();
//                 onStack[popped] = false;
//                 component.add((char) ('A'+popped));
//                 if (id[popped] == low[popped]) break;
//             }
//             components.add(component);
//         }
//     }
// }

import java.util.*;
import java.io.*;

public class TestKattis {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static ArrayList<Integer>[] adj;
    static boolean[] used;
    static Stack<Integer> s;
    static boolean[] onStack, visited;
    static int[] preorder, low;
    static int counter;
    static TreeMap<Character, TreeSet<Character>> components;

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
        while (n != 0) {
            adj = new ArrayList[26];
            used = new boolean[26];
            for (int i= 0; i <= 25; i++) adj[i] = new ArrayList<>();
            while (n-->0) {
                String il = br.readLine();
                int best = il.charAt(10) - 'A';
                for (int i = 0; i <= 8; i += 2) {
                    int curr = il.charAt(i) - 'A';
                    if (curr == best) continue;
                    adj[best].add(curr);
                    used[curr] = true; used[best] = true;
                }
            }
            // for (int i = 0; i <= 25; i++) {
            //     if (!used[i]) continue;
            //     pw.print("adj["+((char)(i+'A'))+"] = ");
            //     for (int next : adj[i]) pw.print((char)(next+'A')+", ");
            //     pw.println();
            // }

            s = new Stack<>();
            onStack = new boolean[26];
            preorder = new int[26]; low = new int[26];
            counter = 0;
            visited = new boolean[26];
            components = new TreeMap<>();
            for (int i = 0; i <= 25; i++) {
                if (!visited[i] && used[i]) dfs(i);
            }
            // pw.println(Arrays.toString(low));
            // pw.println(components);

            for (Map.Entry<Character, TreeSet<Character>> entry : components.entrySet()) {
                for (char node : entry.getValue()) pw.print(node+" ");
                pw.println();
            }
            pw.println();

            n = Integer.parseInt(br.readLine());
        }
    }

    static void dfs(int node) {
        visited[node] = true;
        s.add(node);
        onStack[node] = true;
        preorder[node] = counter;
        low[node] = counter;
        counter++;
        for (int next : adj[node]) {
            if (!visited[next]) dfs(next);

            if (onStack[next]) low[node] = Math.min(low[node], low[next]);
        }

        if (preorder[node] == low[node]) {
            TreeSet<Character> comp = new TreeSet<>();
            while (true) {
                int top = s.pop();
                onStack[top] = false;
                comp.add((char)(top+'A'));

                if (top == node) break;
            }
            components.put(comp.first(), comp);
        }
    }
}
