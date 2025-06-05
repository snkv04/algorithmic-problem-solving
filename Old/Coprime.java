import java.util.*;
import java.io.*;

public class Coprime {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            TreeMap<Integer, Integer> lastIndex = new TreeMap<Integer, Integer>();
            for (int i = n-1; i >= 0; i--) {
                if (!lastIndex.containsKey(a[i])) lastIndex.put(a[i], i+1);
            }
            int[] coprime = new int[1001]; // gives the last index of a number coprime to i
            // for (int i = 1; i <= 1000; i++) coprime[i] = new ArrayList<>();
            for (int i = 1; i <= 1000; i++) {
                for (int j = i; j <= 1000; j++) {
                    if (gcd(Math.max(i, j), Math.min(i, j)) == 1) {
                        if (lastIndex.containsKey(j)) coprime[i] = Math.max(coprime[i], lastIndex.get(j));
                        if (lastIndex.containsKey(i)) coprime[j] = Math.max(coprime[j], lastIndex.get(i));
                    }
                }
            }

            int max = -1;
            for (int i = n-1; i >= 0; i--) {
                if (coprime[a[i]] != 0) max = Math.max(max, i + coprime[a[i]] + 1);
            }
            pw.println(max);
        }

        br.close(); pw.close();
    }

    static int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}
