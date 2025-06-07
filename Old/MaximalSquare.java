import java.util.*;

public class MaximalSquare {
    public static void main(String[] args) {
        // char[][] input = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
        // char[][] input = {{'0', '1'}, {'1', '0'}};
        char[][] input = {{'0', '1'}};
        Solution solution = new Solution();
        System.out.println(solution.maximalSquare(input));
    }
}

class Solution {
    public int maximalSquare(char[][] matrix) {
        int n = matrix.length, m = matrix[0].length;
        int[][] above = new int[n][m],
            left = new int[n][m];
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= m-1; j++) {
                if (matrix[i][j] == '0') {
                    above[i][j] = 0;
                    left[i][j] = 0;
                } else {
                    if (i == 0) {
                        above[i][j] = matrix[i][j]=='1' ? 1 : 0;
                    } else {
                        above[i][j] = matrix[i-1][j]=='1' ? above[i-1][j]+1 : 1;
                    }

                    if (j == 0) {
                        left[i][j] = matrix[i][j]=='1' ? 1 : 0;
                    } else {
                        left[i][j] = matrix[i][j-1]=='1' ? left[i][j-1]+1 : 1;
                    }
                }
            }
        }
        for (int i = 0; i <= n-1; i++) {
            System.out.println("above["+i+"] = " + Arrays.toString(above[i]));
        }
        for (int i = 0; i <= n-1; i++) {
            System.out.println("left["+i+"] = " + Arrays.toString(left[i]));
        }

        int[][] maxSquare = new int[n][m];
        int max = -1;
        for (int i = 0; i <= n-1; i++) maxSquare[i][0] = matrix[i][0]=='1'?1:0;
        for (int j = 0; j <= m-1; j++) maxSquare[0][j] = matrix[0][j]=='1'?1:0;
        for (int i = 1; i <= n-1; i++) {
            for (int j = 1; j <= m-1; j++) {
                if (matrix[i][j] == '0') maxSquare[i][j] = 0;
                else {
                    int maxSize = Math.min(Math.min(above[i-1][j], left[i][j-1]), maxSquare[i-1][j-1]);
                    maxSquare[i][j] = maxSize+1;
                }
            }
        }
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= m-1; j++) {
                max = Math.max(max, maxSquare[i][j]);
            }
        }
        for (int i = 0; i <= n-1; i++) {
            System.out.println("maxSquare["+i+"] = " + Arrays.toString(maxSquare[i]));
        }
        return max * max;
    }
}
