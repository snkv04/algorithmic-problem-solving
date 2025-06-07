import java.util.*;
import java.io.*;

public class TwoChartsBecomeOne {
    static BufferedReader br;
    static PrintWriter pw;
    static String first;
    static String second;
    static HashMap<Integer, HashSet<Integer>> firstTree, secondTree;

    public static void main(String[] args) throws IOException {

        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close();
        pw.close();
    }

    public static void solve() throws IOException {
        StringBuilder sb = new StringBuilder();
        sb.append('(');
        sb.append(br.readLine());
        sb.append(')');
        first = sb.toString();

        sb.setLength(0);
        sb.append('(');
        sb.append(br.readLine());
        sb.append(')');
        second = sb.toString();

        // System.out.println(first);
        // System.out.println(second);

        firstTree = new HashMap<>();
        secondTree = new HashMap<>();
        recurse(true, 0);
        recurse(false, 0);
        // pw.println(firstTree);
        // pw.println(secondTree);

        if (firstTree.size() != secondTree.size()) {
            pw.println("No");
            return;
        }
        for (Map.Entry<Integer, HashSet<Integer>> entry : firstTree.entrySet()) {
            if (!secondTree.containsKey(entry.getKey())) {
                pw.println("No");
                return;
            }

            HashSet<Integer> secondChildren = secondTree.get(entry.getKey());
            if (entry.getValue().size() != secondChildren.size()) {
                pw.println("No");
                return;
            }
            for (int child : entry.getValue()) {
                if (!secondChildren.contains(child)) {
                    pw.println("No");
                    return;
                }
            }
        }
        pw.println("Yes");
    }

    static String recurse(boolean isFirst, int startIdx) {
        int parent = -1;
        HashSet<Integer> children = new HashSet<>();
        int idx = startIdx + 1;
        boolean reachedFirstBreak = false;
        String str = isFirst ? first : second;
        while (true) {
            if (str.charAt(idx) == '(') {
                if (!reachedFirstBreak) {
                    parent = Integer.parseInt(str.substring(startIdx+1, idx).strip());
                    reachedFirstBreak = true;
                }

                String[] result = recurse(isFirst, idx).split(" ");
                int subParent = Integer.parseInt(result[0]), end = Integer.parseInt(result[1]);
                idx = end+1;
                children.add(subParent);
            } else if (str.charAt(idx) == ')') {
                if (!reachedFirstBreak) {
                    parent = Integer.parseInt(str.substring(startIdx+1, idx).strip());
                    reachedFirstBreak = true;
                }

                if (isFirst) {
                    firstTree.put(parent, children);
                    // System.out.println("returning "+parent + " " + idx);
                    return parent + " " + idx;
                } else {
                    secondTree.put(parent, children);
                    return parent + " " + idx;
                }
            } else {
                idx += 1;
            }
        }
    }
}