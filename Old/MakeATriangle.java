import java.util.*;
import java.io.*;

public class MakeATriangle {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int[] sizes = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(sizes);
        int ans = 0;
        while (sizes[0] + sizes[1] <= sizes[2]) {
            ans++;
            sizes[0]++;
        }
        pw.print(ans);

        br.close(); pw.close();
    }
}
