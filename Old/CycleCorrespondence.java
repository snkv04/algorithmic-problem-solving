import java.util.*;
import java.io.*;

public class CycleCorrespondence {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]), k = Integer.parseInt(line[1]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray(),
        b = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        HashSet<Integer> unused = new HashSet<>(); for (int i = 1; i <= n; i++) unused.add(i);
        for (int i = 0; i <= k-1; i++) { unused.remove(a[i]); unused.remove(b[i]); }
        // pw.println(unused);
        int ans = unused.size();
        HashMap<Integer, Integer> amap = new HashMap<>(), bmap = new HashMap<>(), bmap2 = new HashMap<>();
        for (int i = 0; i <= k-1; i++) {
            amap.put(a[i], i);
            bmap.put(b[i], i);
            bmap2.put(b[i], k-1-i);
        }
        // pw.println(bmap); pw.println(bmap2);

        // using array of counts instead of multiset
        int[] dists = new int[k], dists2 = new int[k];
        for (int i = 0; i <= k-1; i++) {
            if (amap.keySet().contains(b[i])) {
                int dist = bmap.get(b[i]) - amap.get(b[i]);
                if (dist < 0) dist += k;
                dists[dist]++;
            }
        }
        for (int i = k-1; i >= 0; i--) {
            if (amap.keySet().contains(b[i])) {
                int dist = bmap2.get(b[i]) - amap.get(b[i]);
                if (dist < 0) dist += k;
                dists2[dist]++;
            }
        }
        // pw.println(Arrays.toString(dists));
        // pw.println(Arrays.toString(dists2));
        int max = 0;
        for (int i = 0; i <= k-1; i++) max = Math.max(max, Math.max(dists[i], dists2[i]));
        ans += max;
        pw.println(ans);

        br.close(); pw.close();
    }
}
