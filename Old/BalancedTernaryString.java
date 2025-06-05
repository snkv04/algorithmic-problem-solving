import java.util.*;
import java.io.*;

public class BalancedTernaryString {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        // int n = Integer.parseInt(br.readLine());
        // char[] s = br.readLine().toCharArray();
        // int[] counts = new int[3];
        // for (char val : s) {
        //     if (val=='0') counts[0]++;
        //     if (val=='1') counts[1]++;
        //     if (val=='2') counts[2]++;
        // }
        // int target = n/3;
        
        // for (int i = 0; i <= n-1 && counts[0] < target && counts[1] > target; i++) {
        //     if (s[i] == '1') {
        //         counts[1]--;
        //         counts[0]++;
        //         s[i] = '0';
        //     }
        // }
        // for (int i = 0; i <= n-1 && counts[0] < target && counts[2] > target; i++) {
        //     if (s[i] == '2') {
        //         counts[2]--;
        //         counts[0]++;
        //         s[i] = '0';
        //     }
        // }

        // for (int i = n-1; i >= 0 && counts[2] < target && counts[1] > target; i--) {
        //     if (s[i] == '1') {
        //         counts[1]--;
        //         counts[2]++;
        //         s[i] = '2';
        //     }
        // }
        // for (int i = n-1; i >= 0 && counts[2] < target && counts[0] > target; i--) {
        //     if (s[i] == '0') {
        //         counts[0]--;
        //         counts[2]++;
        //         s[i] = '2';
        //     }
        // }

        // for (int i = 0; i <= n-1 && counts[1] < target && counts[2] > target; i++) {
        //     if (s[i] == '2') {
        //         counts[2]--;
        //         counts[1]++;
        //         s[i] = '1';
        //     }
        // }
        // for (int i = n-1; i >= 0 && counts[1] < target && counts[0] > target; i--) {
        //     if (s[i] == '0') {
        //         counts[0]--;
        //         counts[1]++;
        //         s[i] = '1';
        //     }
        // }

        // pw.println(s);

        // br.close(); pw.close();

        // see how many 0s, 1s, and 2s needs to be added or removed compared to the target
        // value for all of them, which is n/3. if we need 0s, we want to add them at the
        // left of 1s and 2s. if we need 2s, we want to add them at the right of 0s and 1s.
        // if we need 1s, we want to add them at the left of 2s and at the right of 0s.
        // alternative solution: go from left to right while we need to add 0s, and if
        // the current element needs to be removed then replace it with 0. go from right
        // to left while we need to add 2s, and if the current element needs to be removed
        // then replace it with 2. then, if needed, turn the right-side 0s to 1s and turn
        // the left-side 2s to 1s, based on if 1 needs more appearances. done below.

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        char[] s = br.readLine().toCharArray();
        int[] counts = new int[3];
        for (char val : s) {
            if (val=='0') counts[0]++;
            if (val=='1') counts[1]++;
            if (val=='2') counts[2]++;
        }
        int target = n/3;
        
        for (int i = 0; i <= n-1 && counts[0] < target; i++) {
            if (counts[Character.getNumericValue(s[i])] > target) {
                counts[Character.getNumericValue(s[i])]--;
                counts[0]++;
                s[i] = '0';
            }
        }
        for (int i = n-1; i >= 0 && counts[2] < target; i--) {
            if (counts[Character.getNumericValue(s[i])] > target) {
                counts[Character.getNumericValue(s[i])]--;
                counts[2]++;
                s[i] = '2';
            }
        }
        for (int i = 0; i <= n-1 && counts[1] < target && counts[2] > target; i++) {
            if (s[i] == '2') {
                counts[2]--;
                counts[1]++;
                s[i] = '1';
            }
        }
        for (int i = n-1; i >= 0 && counts[1] < target && counts[0] > target; i--) {
            if (s[i] == '0') {
                counts[0]--;
                counts[1]++;
                s[i] = '1';
            }
        }
        pw.println(s);

        br.close(); pw.close();
    }
}
