import java.util.*;
import java.io.*;

public class SleepingInClass {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for(int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            ArrayList<Integer> logs = new ArrayList<Integer>();
            String[] split = br.readLine().split(" ");
            for(String log: split) {
                logs.add(Integer.parseInt(log));
            }
            
            int min = Integer.MAX_VALUE;
            int max = Integer.MIN_VALUE;
            int total = 0;
            for(int log: logs) {
                if(log < min) min = log;
                if(log > max) max = log;
                total += log;
            }

            int count = 0;
            boolean broke = false;
            for(int j = max; j <= total; j++) {
                int sum = 0;
                count = 0;
                int sections = 0;
                for(int k = 0; k <= logs.size()-1; k++) {
                    if(sum + logs.get(k) < j) {
                        sum += logs.get(k);
                        count++;
                    } else if(sum + logs.get(k) == j) {
                        sum = 0;
                        sections++;
                        count++;
                    } else if(sum + logs.get(k) > j) {
                        break;
                    }

                    // if it makes it to the end of the k loop, that value of j works
                    // except for the case where the last log does not equal all the others
                    if(k == logs.size()-1 && sum == 0) {
                        broke = true;
                    } else if(k == logs.size()-1 && sum != 0) {
                        break;
                    }
                }
                if(broke) {
                    count -= sections;
                    break;
                }
            }
            pw.println(count);
        }

        br.close(); pw.close();
    }
}