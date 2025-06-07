import java.util.*;
import java.io.*;

public class LuoTianyiShow {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            int[] b = Arrays.stream(br.readLine().split(" ")).mapToInt((Integer::parseInt)).toArray();
            int left = 0, right = 0;
            TreeSet<Integer> selections = new TreeSet<Integer>();
            for (int element : b) {
                if (element == -1) left++;
                if (element == -2) right++;
                else selections.add(element);
            }

            
            int ans = Math.min(m, Math.max(left, right));

            int alt = 0;
            int leftPrefix = selections.first()-1;
            int rightPrefix = m-selections.last();
            int gaps = selections.last() - selections.first() - 1 - (selections.size() - 2);
            alt = selections.size();
            alt += Math.min(left, leftPrefix); left -= Math.min(left, leftPrefix);
            alt += Math.min(right, rightPrefix); right -= Math.min(right, rightPrefix);
            alt += Math.min(gaps, left + right);
            ans = Math.max(ans, alt);

            alt = Math.min()
        }

        br.close(); pw.close();
    }
}
