import java.util.*;
import java.io.*;

public class VikaAndTheBridge {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int[] c = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] last = new int[k+1];
            for (int i = 1; i <= k; i++) {
                last[i] = -1;
            }

            Multiset[] segments = new Multiset[k+1];
            for (int i = 1; i <= k; i++) {
                segments[i] = new Multiset();
            }
            
            for (int i = 0; i <= n-1; i++) {
                int color = c[i];
                segments[color].add(i-1-last[color]);
                last[color] = i;
            }
            for (int i = 1; i <= k; i++) segments[i].add(n-1-last[i]);

            int min = (int)3e5;
            for (int i = 1; i <= k; i++) {
                if (k==1) min = Math.min(min, segments[1].mset.lastKey());
                else {
                    int largest = segments[i].mset.lastKey();
                    if (largest%2==1) {
                        int mid = largest/2;
                        segments[i].add(mid);
                        segments[i].add(mid);
                        segments[i].remove(largest);
                        min = Math.min(min, segments[i].mset.lastKey());
                    } else {
                        int mid1 = largest/2;
                        int mid2 = (largest-1)/2;
                        segments[i].add(mid1);
                        segments[i].add(mid2);
                        segments[i].remove(largest);
                        min = Math.min(min, segments[i].mset.lastKey());
                    }
                }
            }
            pw.println(min);
        }

        br.close(); pw.close();
    }

    static class Multiset {
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }
    }
}
