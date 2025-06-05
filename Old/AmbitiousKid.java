import java.util.*;
import java.io.*;

public class AmbitiousKid {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int ans = Integer.MAX_VALUE;
        while (n-->0) {
            int a = sc.nextInt();
            ans = Math.min(ans, Math.abs(a));
        }
        System.out.print(ans);
    }
}
