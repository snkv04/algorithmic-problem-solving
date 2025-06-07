import java.util.*;
import java.io.*;

public class MinimalHeightTree {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            // int lastNum = 1;
            int prevLayerNodes = 1;
            int currLayerNodes = 0;
            int layers = 1;
            for (int j = 1; j <= n-1; j++) {
                if (a[j] > a[j-1]) {
                    currLayerNodes++;
                    // lastNum = a[j];
                } else {
                    prevLayerNodes--;
                    // lastNum = a[j];
                    if (prevLayerNodes == 0) {
                        layers++;
                        prevLayerNodes = currLayerNodes;
                        currLayerNodes = 1;
                    } else {
                        currLayerNodes++;
                    }
                }
            }
            pw.println(layers);
        }

        br.close(); pw.close();
    }
}
