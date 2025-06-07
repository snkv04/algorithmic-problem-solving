import java.util.*;
import java.io.*;

public class ProductOf3Numbers {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <= t; i++) {
            int n = sc.nextInt();
            if (n < 23) {
                pw.println("NO");
                continue;
            }
            int sqrt = (int) Math.sqrt(n);
            TreeSet<Integer> nums = new TreeSet();
            for (int j = 2; j <= sqrt && nums.size() < 2; j++) {
                if (n%j==0) {
                    nums.add(j);
                    n/=j;
                }
            }
            if (nums.size() < 2 || (nums.size()==2 && (n<=2 || n==nums.first() || n==nums.last())))
                pw.println("NO");
            else {
                pw.println("YES");
                pw.println(nums.first() + " " + nums.last() + " " + n);
            }
        }

        sc.close(); pw.close();
    }
}
