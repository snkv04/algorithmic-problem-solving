import java.util.*;
import java.io.*;

public class CowGymnastics {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("gymnastics.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("gymnastics.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        String[] line1 = br.readLine().split(" ");
        int k = Integer.parseInt(line1[0]);
        int n = Integer.parseInt(line1[1]);
        Integer[][] sessions = new Integer[k][n];
        for(int i = 0; i <= k-1; i++) {
            String[] split = br.readLine().split(" ");
            for (int j = 0; j <= n-1; j++) {
                sessions[i][j] = Integer.parseInt(split[j]);
            }
        }

        int count = 0;
        // check if each pair is consistent
        for(int i = 1; i <= n; i++) {
            for(int j = i+1; j <= n; j++) {
                // here, check if the pair is consistent
                int comparison = comparePair(Arrays.asList(sessions[0]).indexOf(i), Arrays.asList(sessions[0]).indexOf(j));
                boolean staysSame = true;
                for(int session = 1; session <= k-1; session++) {
                    int newComp = comparePair(Arrays.asList(sessions[session]).indexOf(i), Arrays.asList(sessions[session]).indexOf(j));
                    if (newComp != comparison) {
                        staysSame = false;
                        break;
                    }
                }

                if (staysSame) count++;
            }
        }

        pw.println(count);

        br.close(); pw.close();
    }

    public static int comparePair(int index1, int index2) {
        if (index1 > index2) {
            return -1;
        } else {
            return 1;
        }
    }
}
