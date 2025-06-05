import java.util.*;
import java.io.*;

public class BovineAcrobatics {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader( new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]), m = Integer.parseInt(line[1]), k = Integer.parseInt(line[2]);
        long[] a = new long[n], w = new long[n];
        TreeSet<Pair> weights = new TreeSet<>(Comparator.comparingLong(o -> o.weight));
        for (int i= 0; i <= n-1; i++) {
            line = br.readLine().split(" ");
            a[i] = Integer.parseInt(line[1]);
            w[i] = Integer.parseInt(line[0]);
            weights.add(new Pair(w[i], a[i]));
        }

        long ans = 0;
        while (m > 0 && !weights.isEmpty()) {
            Pair last = weights.first();
            HashSet<Pair> currTower = new HashSet<>();
            long minCount = Integer.MAX_VALUE;
            while (last != null) {
                currTower.add(last);
                minCount = Math.min(minCount, last.count);
                last = weights.ceiling(new Pair(last.weight+k, -1));
            }

            minCount = Math.min(minCount, m); // will only be set to m on the last tower (if there are enough cows)
            ans += minCount * (long) currTower.size();
            for (Pair pair : currTower) {
                if (weights.ceiling(pair).count == minCount) {
                    weights.remove(weights.ceiling(pair));
                } else {
                    weights.ceiling(pair).count -= minCount;
                }
            }
            m -= minCount;
        }
        pw.println(ans);

        br.close(); pw.close();
    }

    static class Pair {
        long weight, count;

        public Pair(long weight, long count) {
            this.weight = weight;
            this.count = count;
        }

        public String toString() {
            return "(wt="+weight+", cnt="+count+")";
        }
    }
}
