import java.util.*;
import java.io.*;

public class SquareFilling {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        int[][] A = new int[n][m];
        for (int i = 0; i <= n-1; i++) {
            line = br.readLine().split(" ");
            for (int j = 0; j <= m-1; j++) {
                A[i][j] = Integer.parseInt(line[j]);
            }
        }
        
        // boolean works = true;
        // for (int i = 0; i <= n-2 && works; i++) {
        //     for (int j = 0; j <= n-2; j++) {
        //         if ((A[i][j]==1&&A[i+1][j]==1) && (A[i][j+1]==0&&A[i+1][j+1]==0)
        //             && (j-1 < 0 || A[i][j-1]==0 || A[i+1][j-1]==0)) {
                    
        //             works = false;
        //             break;
        //         }
        //         if ((A[i][j]==1&&A[i][j+1]==1) && (A[i+1][j]==0&&A[i+1][j+1]==0)
        //             && (i-1<0 || A[i-1][j]==0 || A[i-1][j+1]==0)) {
                    
        //             works = false;
        //             break;
        //         }
        //         if (A[i][j]==1 && A[i][j+1]==0 && A[i+1][j]==0 && A[i+1][j+1]==0
        //             && (i-1 < 0 || j-1 < 0 || A[i-1][j]==0 || A[i][j-1]==0 || A[i-1][j-1]==0)) {

        //             works = false;
        //             break;
        //         }
        //     }
        // }
        // for (int i = n-1; i >= 1; i--) {
        //     if (A[i][m-1]==1 && (A[i-1][m-1]==0 || A[i][m-2]==0 || A[i-1][m-2]==0)) {
        //         works = false;break;
        //     }
        // }
        // for (int j = m-2; j >= 1; j--) {
        //     if (A[n-1][j]==1 && (A[n-1][j-1]==0 || A[n-2][j]==0 || A[n-2][j-1]==0)) {
        //         works = false;
        //         break;
        //     }
        // }
        
        // if (!works) {
        //     pw.println(-1);
        //     pw.close();
        //     return;
        // }
        // int[][] B = new int[n][m];
        // int ans = 0;
        // ArrayList<String> ops = new ArrayList<>();
        // for (int i = 0; i <= n-2; i++) {
        //     for (int j = 0; j <= m-2; j++) {
        //         if (A[i][j]==1 && A[i][j+1]==1 && A[i+1][j]==1 && A[i+1][j+1]==1) {
        //             B[i][j]=1;
        //             B[i][j+1]=1;
        //             B[i+1][j]=1;
        //             B[i+1][j+1]=1;
        //             ops.add(i + " "+ j);
        //             ans++;
        //         }
        //     }
        // }
        // pw.println(ans);
        // for (String operation : ops) pw.println(operation);

        // instead of going through and checking every square to see if it's fine with the
        // style of operation we're doing on the matrix, since that is both a lot of work
        // and a lot of potentially confusing/easy-to-get-wrong details, just go through and
        // do all the operations on B where the corresponding square in A is filled in, then
        // go back and check if B fully equals A. if it does, then that means A could be done
        // with the operations. if it doesn't, then that means that A has some squares that
        // couldn't be filled in using these operations, meaning filling in B in the same
        // way is impossible and the ans is -1.
        int[][] B = new int[n][m];
        int ans = 0;
        ArrayList<String> ops = new ArrayList();
        for (int i = 0; i <= n-2; i++) {
            for (int j= 0; j <= m-2; j++) {
                if (A[i][j]==1 && A[i][j+1]==1 && A[i+1][j]==1 && A[i+1][j+1]==1) {
                    B[i][j]=1;
                    B[i][j+1]=1;
                    B[i+1][j]=1;
                    B[i+1][j+1]=1;
                    ops.add((i+1) + " "+ (j+1));
                    ans++;
                }
            }
        }

        boolean works = true;
        for (int i = 0; i <= n-1 && works; i++) {
            for (int j= 0; j <= m-1; j++) {
                if (A[i][j] != B[i][j]) {
                    works = false;
                    break;
                }
            }
        }

        if (!works) {
            pw.println(-1);
            pw.close();
            return;
        }
        pw.println(ans);
        for (String operation : ops) pw.println(operation);

        br.close(); pw.close();
    }
}
