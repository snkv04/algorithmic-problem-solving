import java.util.*;
import java.io.*;

public class ChallengeKattis {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        for (int i = 1; i <= t; i++) {
            pw.print("Case #"+i+": ");
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] inp = br.readLine().split(" ");
        char[] num = inp[0].toCharArray();
        char[] source = inp[1].toCharArray();
        char[] dest = inp[2].toCharArray();
        HashMap<Character, Integer> map = new HashMap<>();
        HashMap<Integer, Character> map2 = new HashMap<>();
        for (int i = 0; i <= source.length-1; i++) map.put(source[i], i);
        for (int i = 0; i <= dest.length-1; i++) map2.put(i, dest[i]);

        long translated = 0;
        long multiplier = 1;
        for (int i = 0; i <= num.length-1; i++) {
            int digit = map.get(num[num.length-1-i]);
            translated += digit * multiplier;
            multiplier *= map.size();
        }
        // pw.println(translated);
        // pw.println(map);
        // pw.println(map2);

        Stack<Character> translated2 = new Stack<>();
        while (translated > 0) {
            long rem = translated % map2.size();
            translated /= map2.size();
            translated2.add(map2.get((int)rem));
        }
        while (!translated2.isEmpty()) {
            pw.print(translated2.pop());
        }
        pw.println();
    }
}
