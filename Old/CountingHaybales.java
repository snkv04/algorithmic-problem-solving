import java.util.*;
import java.io.*;

public class CountingHaybales {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("haybales.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("haybales.out")));

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int q = Integer.parseInt(line[1]);
        int[] bales = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(bales);
        TreeMap<Integer, Integer> sortedBales = new TreeMap<>();
        for (int i = 0; i <= n-1; i++) {
            sortedBales.put(bales[i], i);
        }

        for (int i = 1; i <= q; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            if (b < sortedBales.firstKey() || a > sortedBales.lastKey()) pw.println(0);
            else pw.println(sortedBales.get(sortedBales.floorKey(b)) - sortedBales.get(sortedBales.ceilingKey(a)) + 1);
        }

        br.close(); pw.close();
    }
}
