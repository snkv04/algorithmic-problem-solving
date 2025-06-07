import java.util.*;
import java.io.*;

public class RestoreTheWeather {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            Integer[][] weatherToIndex = new Integer[n][2];
            for (int j = 0; j <= n-1; j++) {
                weatherToIndex[j][0] = a[j];
                weatherToIndex[j][1] = j;
            }
            Arrays.sort(weatherToIndex, Comparator.comparing(obj -> obj[0]));
            int[] b = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            Integer[] bForSorting = new Integer[n]; for (int j = 0; j <= n-1; j++) bForSorting[j] = b[j];
            Arrays.sort(bForSorting);
            for (int j = 0; j <= n-1; j++) {
                a[weatherToIndex[j][1]] = bForSorting[j];
            }
            
            for (int j =0; j<=n-1;j++) {
                pw.print(a[j] + " ");
            }
            pw.println();
        }

        br.close(); pw.close();
    }
}
