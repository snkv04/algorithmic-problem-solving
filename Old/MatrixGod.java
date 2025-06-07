import java.util.*;
import java.io.*;

public class MatrixGod {
    static int MOD = (int) 1e9 + 7;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        long[][] a = new long[n][n], b = new long[n][n], c = new long[n][n];
        for (int i = 0; i < 3 * n; ++i) {
            // for (int j = 0; j < n; ++j) {
                if (i < n) {
                    a[i] = Arrays.stream(br.readLine().split(" ")).mapToLong(Integer::parseInt).toArray();
                } else if (i < 2*n) {
                    b[i%n] = Arrays.stream(br.readLine().split(" ")).mapToLong(Long::parseLong).toArray();
                } else {
                    c[i%n] = Arrays.stream(br.readLine().split(" ")).mapToLong(Integer::parseInt).toArray();
                }
            // }
        }

        int tests = 12;
        while (tests-->0) {
            long[][] vec = new long[n][1];
            for (int i = 0; i < n; ++i) {
                vec[i][0] = (int) (Math.random() * 1e9);
            }

            long[][] abv = matmul(a, matmul(b, vec));
            long[][] cv = matmul(c, vec);
            for (int i = 0; i < n; ++i) {
                if (abv[i][0] != cv[i][0]) {
                    pw.println("NO");
                    pw.close();
                    return;
                }
            }
        }
        pw.println("YES");

        br.close();
        pw.close();
    }

    static long[][] matmul(long[][] a, long[][] b) {
        assert a[0].length == b.length : "Invalid sizes";
        long[][] result = new long[a.length][b[0].length];
        for (int i = 0; i < result.length; ++i) {
            for (int j = 0; j < result[0].length; ++j) {
                for (int k = 0; k < a[0].length; ++k) {
                    result[i][j] += a[i][k] * b[k][j];
                    if (result[i][j] > MOD) {
                        result[i][j] %= MOD;
                    }
                }
            }
        }
        return result;
    }
}