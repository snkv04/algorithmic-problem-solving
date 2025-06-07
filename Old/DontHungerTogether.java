import java.util.*;
import java.io.*;

public class DontHungerTogether {
    static BufferedReader br;
    static PrintWriter pw;
    static double[][] input;
    static double n, k;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] a = br.readLine().split(" ");
        n = Integer.parseInt(a[0]); k = Integer.parseInt(a[1]);
        input = new double[(int)n][2];
        for (int i = 0; i < n; i++) {
            a = br.readLine().split(" ");
            input[i][0] = Double.parseDouble(a[0]) / k;
            input[i][1] = Double.parseDouble(a[1]) - 1;
        }

        double l = 0, r = 1e9, ans = -1;
        for (int i = 0; i < 70; i++) {
            double mid = (l + r) / 2;
            if (check(mid)) {
                ans = l = mid;
            } else {
                r = mid;
            }
        }
        pw.println(ans<=1e-9?((int)-1):ans);
    }

    static boolean check(double mid) {
        PriorityQueue<Pair> available = new PriorityQueue<>(Comparator.comparingInt(o -> o.end));
        for (int i = 0; i < n; i++) {
            while (!available.isEmpty() && available.peek().end < i) {
                available.poll();
            }

            available.add(new Pair(input[i][0], (int) input[i][1]));

            double mustEat = mid;
            while (mustEat > 0 && !available.isEmpty()) {
                Pair food = available.poll();
                if (food.amount > mustEat) {
                    food.amount -= mustEat;
                    available.add(food);
                    mustEat = 0;
                } else if (food.amount == mustEat) {
                    mustEat = 0;
                } else {
                    mustEat -= food.amount;
                }
            }

            if (mustEat > 0) return false; 
        }
        return true;
    }

    static class Pair {
        double amount;
        int end;

        public Pair(double amount, int end) {
            this.amount = amount;
            this.end = end;
        }
    }
}