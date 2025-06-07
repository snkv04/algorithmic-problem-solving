import java.util.*;
import java.io.*;

public class MilkingOrder {
    static int[] order;
    static int[] line;
    static int[] positions;
    static int n, m;
    static HashSet<Integer> remaining;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new FileReader("milkorder.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("milkorder.out")));

        n = sc.nextInt();
        m = sc.nextInt();
        int k = sc.nextInt();
        order = new int[m];
        boolean oneInOrder = false;
        for (int i = 0; i <= m-1; i++) {
            order[i] = sc.nextInt();
            if (order[i]==1) oneInOrder=true;
        }
        remaining = new HashSet();
        for (int i = 1; i <= n; i++) remaining.add(i);
        line = new int[n+1]; // gives the cow at position i
        positions = new int[n+1]; // gives the position of cow i
        for (int i = 1; i <= k; i++) {
            int ci = sc.nextInt();
            int pi = sc.nextInt();
            line[pi] = ci;
            positions[ci] = pi;
            remaining.remove(ci);
        }
        placeOrderedCows(oneInOrder);
        
        if (!remaining.contains(1)) {
            pw.println(positions[1]);
            pw.close();
            return;
        }
        int ans = -1;
        for (int i = 1; i <= n; i++) {
            if (line[i]==0) {
                ans = i; break;
            }
        }
        pw.println(ans);

        sc.close(); pw.close();
    }

    static void placeOrderedCows(boolean oneInOrder) {
        if (oneInOrder) {
            for (int i = 0; i <= m-1; i++) {
                if (!remaining.contains(order[i])) continue;

                int leftBound = i==0?0:positions[order[i-1]];
                for (int j = leftBound+1; j <= n; j++) {
                    if (line[j]==0) {
                        remaining.remove(order[i]);
                        line[j] = order[i];
                        positions[order[i]] = j;
                        break;
                    }
                }
            }
        } else {
            for (int i = m-1; i >= 0; i--) {
                if (!remaining.contains(order[i])) continue;

                int rightBOund = i==m-1?n+1:positions[order[i+1]];
                for (int j = rightBOund-1; j >= 1; j--) {
                    if (line[j]==0) {
                        remaining.remove(order[i]);
                        line[j] = order[i];
                        positions[order[i]] = j;
                        break;
                    }
                }
            }
        }
    }
}
