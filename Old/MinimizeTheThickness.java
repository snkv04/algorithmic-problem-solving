import java.util.*;
import java.io.*;

public class MinimizeTheThickness {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int sum = 0;
            for (int num : a) sum += num;

            int minLength = 3000;
            for (int segments = 1; segments <= n; segments++) {
                if (sum % segments != 0) continue;

                int eachSum = sum / segments;
                int currSum = 0;
                int maxLength = -1;
                int start = -1;
                boolean works = true;
                for (int i = 0; i <= n-1; i++) {
                    currSum += a[i];
                    if (currSum == eachSum) {
                        maxLength = Math.max(maxLength, i-start);
                        start = i;
                        currSum = 0;
                    } else if (currSum > eachSum) {
                        works = false;
                        break;
                    }
                }
                if (currSum < eachSum && currSum != 0) works = false;

                if (works) {
                    minLength = Math.min(minLength, maxLength);
                }
            }
            pw.println(minLength);
        }

        br.close(); pw.close();
    }
}
