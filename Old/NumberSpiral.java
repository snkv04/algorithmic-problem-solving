import java.util.*;
import java.io.*;

public class NumberSpiral {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for(int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            long row = Long.parseLong(line[0]);
            long col = Long.parseLong(line[1]);
            long curr_layer = Math.max(row, col);
            long prev_layer = curr_layer - 1;
            long result;
            if (prev_layer % 2 == 0) {
                // current layer is odd
                if (row < col) result = (long) (curr_layer * curr_layer - row + 1);
                else result = (long) (prev_layer * prev_layer + col);
            } else {
                // current layer is even
                if (row > col) result = (long) (curr_layer * curr_layer - col + 1);
                else result = (long) (prev_layer * prev_layer + row);
            }
            pw.println(result);
        }

        br.close(); pw.close();
    }
}
