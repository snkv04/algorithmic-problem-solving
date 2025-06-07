import java.util.*;
import java.io.*;

public class UnreadMessages {
    static BufferedReader br;
    static PrintWriter pw;

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
        String[] asdf = br.readLine().split(" ");
        int n = Integer.parseInt(asdf[0]), m = Integer.parseInt(asdf[1]);
        long current = 0;
        HashMap<Integer, Integer> last = new HashMap<>();
        int soFar = 0;
        while (m-- > 0) {
            soFar++;
            current += n;
            int message = Integer.parseInt(br.readLine());
            if (!last.containsKey(message)) {
                current -= soFar;
            } else {
                current -= soFar - last.get(message);
            }
            last.put(message, soFar);
            pw.println(current);
        }
    }
}