import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class OvalWatch {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]), k = Integer.parseInt(line[1]);
        TreeSet<Pair>[] attachedLegs = new TreeSet[n];
        for (int i = 0; i <= n-1; i++) {
            attachedLegs[i] = new TreeSet<Pair>(Comparator.comparingInt(o -> o.b));
        }
        while (k-->0) {
            line = br.readLine().split(" ");
            int left = Integer.parseInt(line[0]), right = left+1, dist = Integer.parseInt(line[1]);
            attachedLegs[left].add(new Pair(+1, dist));
            attachedLegs[right].add(new Pair(-1, dist));
        }

        for (int i = 0; i <= n-1; i++) {
            int currLine = i, currHeight = 0;
            while (attachedLegs[currLine].higher(new Pair(-1, currHeight)) != null) {
                Pair higher = attachedLegs[currLine].higher(new Pair(-1, currHeight));
                currLine += higher.a;
                currHeight = higher.b;
            }
            pw.print(currLine+" ");
        }
    }

    static class Pair {
        int a, b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
        
        // @Override
        // public boolean equals(Object obj) {
        //     if (this == obj) return true;
        //     if (obj == null) return false;
        //     if (!(obj instanceof Pair)) return false;

        //     Pair other = (Pair) obj;
        //     return this.a == other.a && this.b == other.b;
        // }

        // @Override
        // public int hashCode() {
        //     return (this.a+" "+this.b).hashCode();
        // }
    }
}
