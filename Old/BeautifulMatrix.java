import java.util.*;
import java.io.*;

public class BeautifulMatrix {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int[][] matrix = new int[5][5];
        int ans = 0;
        for (int i = 0; i <= 4; i++) {
            for (int j = 0; j <= 4; j++) {
                matrix[i][j]=sc.nextInt();
                if (matrix[i][j]==1) {
                    ans = Math.abs(i-2)+Math.abs(j-2);
                    break;
                }
            }
        }
        pw.println(ans);

        sc.close(); pw.close();
    }
}
