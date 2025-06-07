import java.util.*;
import java.io.*;

public class DifferenceOfGCDs {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // Scanner sc = new Scanner(System.in);
        // for (int i = 1; i <= 9; i++) System.out.println("i="+i+", and gcd is "+gcd(i, sc.nextInt()));
        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            // String[] line = br.readLine().split(" ");
            // int n = Integer.parseInt(line[0]);
            // int l = Integer.parseInt(line[1]);
            // int r = Integer.parseInt(line[2]);
            // int[] a = new int[n];
            // int i = 0;
            // // TreeSet<Integer> used = new TreeSet<Integer>();
            // while (i <= n-1) {
            //     boolean found = false;
            //     int start;
            //     if (l%(i+1)==0) {
            //         start=l;
            //     } else {
            //         start = (l/(i+1) + 1) * (i+1);
            //     }
            //     for (int j = start; j <= r; j += (i+1)) {
            //         // if (!used.contains(j)) {
            //             // used.add(j);
            //             a[i]=j;
            //             found = true;
            //             break;
            //         // }
            //     }
            //     if (!found) break;
            //     i++;
            // }
            // if (i == n) {
            //     pw.println("YES");
            //     for (int ai : a) pw.print(ai + " ");
            //     pw.println();
            // } else pw.println("NO");

            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int l = Integer.parseInt(line[1]);
            int r = Integer.parseInt(line[2]);
            ArrayList<Integer> nums = new ArrayList<>();
            for (int i = 1; i <= n; i++) {
                int test = (l/i)*i;
                if (test < l) {
                    if (test+i > r) {
                        break;
                    } else {
                        nums.add(test+i);
                    }
                } else {
                    nums.add(test);
                }
            }
            if (nums.size() != n) pw.println("NO");
            else { pw.println("YES"); for (int num : nums) pw.print(num + " "); pw.println(); }
        }

        br.close(); pw.close();
    }

    static int gcd(int a, int b) {
        int temp = Math.max(a, b);
        b = Math.min(a, b);
        a = temp;
        while (b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}
