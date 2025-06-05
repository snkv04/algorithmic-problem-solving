import java.util.*;
import java.io.*;

public class BalancedTeam {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        Integer[] a = new Integer[n];
        for (int i = 0; i <= n-1; i++) a[i] = sc.nextInt();
        Arrays.sort(a);
        int i=0, j=0;
        int ans = 1;
        while (j <= n-1) {
            // keep i fixed while j can still move
            int valueAtI = a[i];
            while (j<=n-1 && a[j]<=valueAtI+5) {
                ans = Math.max(ans, j-i+1);
                j++;
            }
            i++;
        }
        pw.println(ans);

        sc.close(); pw.close();

        // first obviously sort the array so that the elements with the least
        // gap in value are closest. then, since we want to find the max number
        // of people where the person with the min skill and the one with the max
        // skill have a diff of <= 5, we can have two pointers cover the subarray
        // that we are including in the team that we are trying to maximize. if
        // the element at the second pointer is <= 5 away from the element at the
        // first pointer, we can record the length of the array and keep moving it
        // until it's no longer true. once it's no longer true, then we move the
        // first pointer forward. however, if it stays true until the end of the
        // array while the first pointer stays fixed, then this logic still works.
    }
}
