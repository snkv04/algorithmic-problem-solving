import java.util.*;
import java.io.*;

public class SumOfRoundNumbers {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int i = 1;
            ArrayList<Integer> nums = new ArrayList<>();
            while (n>0) {
                int digit = n%10;
                if (digit*i != 0)
                    nums.add(digit*i);
                i *= 10;
                n /= 10;
            }
            pw.println(nums.size());
            for (int num : nums) pw.print(num + " ");
            pw.println();
        }

        br.close(); pw.close();
    }
}
