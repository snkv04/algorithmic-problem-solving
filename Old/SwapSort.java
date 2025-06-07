import java.util.*;
import java.io.*;

public class SwapSort {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] sorted = Arrays.copyOf(a, n);
        Arrays.sort(sorted);
        ArrayList<Pair> swaps = new ArrayList<>();
        for (int i = 0; i <= n-1; i++) {
            int want = sorted[i];
            if (a[i] != want) {
                for (int j = i+1; j <= n-1; j++) {
                    if (a[j] == want && sorted[j] != want) {
                        swaps.add(new Pair(i, j));
                        int temp = a[j];
                        a[j] = a[i];
                        a[i] = temp;
                        break;
                    }
                }
            }
        }
        pw.println(swaps.size());
        for (Pair swap : swaps) pw.println(swap.first + " " + swap.second);

        br.close(); pw.close();
    }

    static class Pair {
        int first, second;

        public Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }
    }
}
