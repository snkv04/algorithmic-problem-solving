import java.util.*;
import java.io.*;

public class DaisyChains {
    static TreeMap<Integer, Integer> multiset;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int count = 0;
        for (int i = 0; i <= n-1; i++) {
            multiset = new TreeMap<>();
            double sum = 0;
            for (int j = i; j <= n-1; j++) {
                add(p[j]);
                sum += p[j];
                if (sum / (j-i+1) % 1 == 0) {
                    if (multiset.containsKey((int) (sum / (j-i+1)))) {
                        count++;
                    }
                }
            }
        }
        pw.println(count);

        br.close(); pw.close();
    }

    static void add(int x) {
        if (multiset.containsKey(x)) {
            multiset.put(x, multiset.get(x)+1);
        } else {
            multiset.put(x, 1);
        }
    }

    // static void remove(int x) {
    //     multiset.put(x, multiset.get(x)-1);
    //     if (multiset.get(x)==0) multiset.remove(x);
    // }
}
