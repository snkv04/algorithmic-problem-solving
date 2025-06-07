import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class GameRank {
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
        TreeMap<Integer, Integer> spr = new TreeMap<>();
        for (int i = 0; i <= 19; i++) {
            spr.put(25-i, 2+(i/5));
        }
        for (int i = 1; i <= 10; i++) spr.put(i, 5);
        // System.out.println(spr);

        char[] history = br.readLine().toCharArray();
        int winstreak = 0;
        int rank = 25, stars = 0;
        for (char c : history) {
            if (c == 'W') {
                winstreak++;
                int gain = 1;
                if (rank <= 25 && rank >= 6 && winstreak >= 3) {
                    gain = 2;
                }
                stars += gain;
                
                if (stars > spr.get(rank)) {
                    stars -= spr.get(rank);
                    rank--;
                }
                if (rank == 0) {
                    break;
                }
            } else {
                winstreak = 0;
                if (rank <= 20 && !(rank == 20 && stars == 0)) {
                    if (stars == 0) {
                        rank++;
                        stars = spr.get(rank) - 1;
                    } else {
                        stars--;
                    }
                }
            }
        }
        pw.println(rank==0?"Legend":rank);
    }
}
