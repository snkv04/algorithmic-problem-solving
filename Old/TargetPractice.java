import java.util.*;
import java.io.*;

public class TargetPractice {
    static HashMap<Character, Integer> map;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader( new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int t = Integer.parseInt(line[0]);
        int c = Integer.parseInt(line[1]);
        int[] _targets = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        HashSet<Integer> targets = new HashSet<>(); for (int target : _targets) targets.add(target);
        char[] commands = br.readLine().toCharArray();
        map = new HashMap<>();
        map.put('F', 0);
        map.put('L', -1);
        map.put('R', 1);

        // 0 = 0, 1 = 1, 2 = 2, 3 = -1, 4 = -2
        int[][] loc = new int[c+1][5];
        for (int i = 0; i <= c; i++) {
            if (i >= 1) loc[i][0] = loc[i-1][0] + map.get(commands[i-1]);

            for (int j = 0; j <= 4; j++) {
                loc[i][j] = loc[i][0] + j;
                if (j == 3) loc[i][j] = loc[i][0] - 1;
                if (j == 4) loc[i][j] = loc[i][0] - 2;
            }
        }
        // for (int i = 0; i <= c; i++) pw.println(Arrays.toString(loc[i]));

        Multiset[] multisets = new Multiset[5]; for (int i = 0; i <= 4; i++) multisets[i] = new Multiset();
        for (int i = c; i >= 1; i--) {
            for (int j = 0; j <= 4; j++) {
                if (commands[i-1] == 'F' && targets.contains(loc[i][j])) {
                    multisets[j].add(loc[i][j]);
                }
            }
        }

        int max = 0;
        for (int i = 1; i <= c; i++) {
            // removes any targets hit from the shifted location(s) at the current command
            for (int j = 0; j <= 4; j++) {
                if (commands[i-1] == 'F' && targets.contains(loc[i][j])) {
                    multisets[j].remove(loc[i][j]);
                }
            }

            // iterates through different possibilities for current command
            int currCommand = map.get(commands[i-1]);
            for (int j = -1; j <= 1; j++) { // includes both changing and not changing command
                int diff = j - currCommand;
                if (diff < 0) diff = 2 + Math.abs(diff);
                if (j == 0 && targets.contains(loc[i][diff])) {
                    multisets[diff].add(loc[i][diff]);
                }
                max = Math.max(max, multisets[diff].ms.size());
                if (j == 0 && targets.contains(loc[i][diff])) {
                    multisets[diff].remove(loc[i][diff]);
                }
            }

            // adds any targets hit from the unshifted location at the current command
            for (int j = 0; j <= 4; j++) {
                if (commands[i-1] == 'F' && targets.contains(loc[i][0])) {
                    multisets[j].add(loc[i][0]);
                }
            }
        }
        pw.println(max);

        br.close(); pw.close();
    }

    static class Multiset {
        HashMap<Integer, Integer> ms;

        public Multiset() {
            ms = new HashMap<>();
        }

        public void add(int x) {
            if (ms.containsKey(x)) ms.put(x, ms.get(x)+1);
            else ms.put(x, 1);
        }

        public void remove(int x) {
            ms.put(x, ms.get(x)-1);
            if (ms.get(x)==0) ms.remove(x);
        }
    }
}
