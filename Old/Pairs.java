import java.util.*;
import java.io.*;

public class Pairs {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int m = sc.nextInt();
        ArrayList<Pair> pairs = new ArrayList<Pair>();
        for (int i = 1; i <= m; i++) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            pairs.add(new Pair(a, b));
        }
        int x1 = pairs.get(0).one;
        int numx = 0;
        int[] counts = new int[n+1];
        for (int i = 0; i <= m-1; i++) {
            if (pairs.get(i).one != x1 && pairs.get(i).two != x1) {
                counts[pairs.get(i).one]++;
                if (pairs.get(i).two != pairs.get(i).one) counts[pairs.get(i).two]++;
            } else {
                numx++;
            }
        }
        Arrays.sort(counts);
        if (numx + counts[n] == m) {
            pw.println("YES");
            pw.close();
            return;
        }
    
        int x2 = pairs.get(0).two;
        numx = 0;
        counts = new int[n+1];
        for (int i = 0; i <= m-1; i++) {
            if (pairs.get(i).one != x2 && pairs.get(i).two != x2) {
                counts[pairs.get(i).one]++;
                if (pairs.get(i).two != pairs.get(i).one) counts[pairs.get(i).two]++;
            } else {
                numx++;
            }
        }
        Arrays.sort(counts);
        if (numx + counts[n] == m) {
            pw.println("YES");
            pw.close();
            return;
        }
        pw.println("NO");

        sc.close(); pw.close();

        // the key observation is that one of x and y, let's say without loss of
        // generalization that it's x, is either the first pair's first element
        // or second element.
        // first try setting x to be the first pair's first element. for every pair,
        // if there is an x in it then we increment the count of x, and if there isn't,
        // then we increment the counts of the two values (one if they're the same) in
        // the pair. at the end, we sort the counts array so that we can take the maximum
        // count as y. if the number of pairs with x and the number of pairs that
        // share a value with (the most shared value across all pairs) equals all of
        // the pairs, then we're good. if not, then we'll try fixing x to be the
        // other value from the first pair. if the same thing doesn't work for the
        // other value of x, then it's not possible.
    }

    static class Pair {
        int one, two;

        public Pair(int one, int two) {
            this.one = one;
            this.two = two;
        }
    }
}
