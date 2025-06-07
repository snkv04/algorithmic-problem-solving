import java.util.*;
import java.io.*;

public class JustStalling {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int[] cows = new int[n];
        for (int i = 0; i <= n-1; i++) cows[i] = sc.nextInt();
        Arrays.sort(cows);
        TreeSet<Pair> sortedCows = new TreeSet();
        for (int i = 0; i <= n-1; i++) sortedCows.add(new Pair(cows[i], i+1));
        int[] barns = new int[n];
        for (int i = 0; i <= n-1; i++) barns[i] = sc.nextInt();
        Arrays.sort(barns);

        long count = 1;
        for (int i = 0; i <= n-1; i++) {
            int barn = barns[i];
            count *= Math.max(0, sortedCows.floor(new Pair(barn, 2*n)).second-i);
        }
        pw.println(count);

        sc.close(); pw.close();
    }

    static class Pair implements Comparable<Pair> {
        int first, second;

        public Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }

        public int compareTo(Pair other) {
            if (this.first != other.first) return Integer.compare(this.first, other.first);
            else return Integer.compare(this.second, other.second);
        }
    }
}
