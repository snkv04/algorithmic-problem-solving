import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class NotAmused {
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
        String line;
        int day = 0;
        TreeMap<String, Integer> counts = new TreeMap<>();
        HashMap<String, Integer> current = new HashMap<>();
        while ((line = br.readLine()) != null) {
            if (line.equals("OPEN")) {
                day++;
                counts = new TreeMap<>();
                current = new HashMap<>();
            } else if (line.equals("CLOSE")) {
                if (day > 1) {
                    pw.println();
                }
                pw.println("Day " + day);
                for (Map.Entry<String, Integer> entry : counts.entrySet()) {
                    double cost = 0.1 * entry.getValue();
                    pw.println(entry.getKey()+" $"+String.format("%.2f", cost));
                }
            } else if (line.startsWith("ENT")) {
                String[] split = line.split(" ");
                String name = split[1];
                int time = Integer.parseInt(split[2]);
                current.put(name, time);
            } else if (line.startsWith("EX")) {
                String[] split = line.split(" ");
                String name = split[1];
                int time = Integer.parseInt(split[2]);
                int startTime = current.remove(name);
                if (!counts.containsKey(name)) {
                    counts.put(name, 0);
                }
                counts.put(name, counts.get(name) + (time - startTime));
            } else {
                break;
            }
        }
    }
}
