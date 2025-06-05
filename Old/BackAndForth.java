import java.util.*;
import java.io.*;

public class BackAndForth {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new FileReader("backforth.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("backforth.out", false)));

        int[] first = new int[10];
        int[] second = new int[10];
        for (int i = 0; i <= 9; i++) first[i] = sc.nextInt();
        for (int i = 0; i <= 9; i++) second[i] = sc.nextInt();

        int[][] possibilities = new int[12100][4];
        int i = 0;
        for (int a = 0; a <= 9; a++) {
            for (int b = 0; b <= 10; b++) {
                for (int c = 0; c <= 9; c++) {
                    for (int d = 0; d <= 10; d++) {
                        possibilities[i][0] = a;
                        possibilities[i][1] = b;
                        possibilities[i][2] = c;
                        possibilities[i][3] = d;
                        i++;
                    }
                }
            }
        }
        // for (int[] possibility : possibilities) pw.println(Arrays.toString(possibility));

        HashSet<Integer> results = new HashSet<Integer>();
        for (int j = 0; j <= 12099; j++) {
            ArrayList<Integer> f = new ArrayList<>();
            ArrayList<Integer> s = new ArrayList<>();
            for (int val : first) f.add(val);
            for (int val : second) s.add(val);
            int a = possibilities[j][0];
            int b = possibilities[j][1];
            int c = possibilities[j][2];
            int d = possibilities[j][3];
            int sum = 1000;
            sum -= f.get(a);
            s.add(f.remove(a));
            sum += s.get(b);
            f.add(s.remove(b));
            sum -= f.get(c);
            s.add(f.remove(c));
            sum += s.get(d);
            results.add(sum);
        }
        pw.println(results.size());

        sc.close(); pw.close();
    }
}
