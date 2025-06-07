import java.util.*;
import java.io.*;

public class SumOfTwoValues {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int x = Integer.parseInt(line[1]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        TreeSet<Two> set = new TreeSet<>();
        for (int i = 0; i <= n-1; i++) {
            set.add(new Two(a[i], i+1));
        }
        // int i=0, j=n-1;
        while (set.size() >= 2) {
            if (set.last().value + set.first().value > x) {
                set.pollLast();
            } else if (set.first().value + set.last().value < x) {
                set.pollFirst();
            } else {
                pw.println(set.first().index + " " + set.last().index);
                break;
            }
        }
        if (set.size() < 2) pw.println("IMPOSSIBLE");

        br.close(); pw.close();
    }

    static class Two implements Comparable<Two> {
        int value, index;

        public Two(int value, int index) {
            this.value = value;
            this.index = index;
        }
        
        public int compareTo(Two other) {
            if (this.value != other.value) return Integer.compare(this.value, other.value);
            else return Integer.compare(this.index, other.index);
        }
    }
}