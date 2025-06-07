import java.util.*;
import java.io.*;

public class SleepingInClass {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for(int i = 1; i <= t; i++) {
            // the logs can be thought of as bar graphs with each class period representing a bar
            // have a while loop that runs as long as the minimum value is not equal to the maximum value
            // take the absolute minimum bar and look at the two adjacent bars
            // combine the minimum bar and the lower of the two that are next to it
            // each combination, increment a count
            // print a count of the number of combinations (modifications) done before the min = max
            // combining two class periods (making a modification) will never result in a value
            // that is lower than either of the two, so either all the logs end up at the initial
            // maximum or a higher value
            int n = Integer.parseInt(br.readLine());
            ArrayList<Integer> logs = new ArrayList<Integer>();
            ArrayList<Integer> sorted = new ArrayList<Integer>();
            String[] split = br.readLine().split(" ");
            for(String log: split) {
                logs.add(Integer.parseInt(log));
                sorted.add(Integer.parseInt(log));
            }
            Collections.sort(sorted);

            int count = 0;
            // int min = sorted.get(0);
            // int max = sorted.get(sorted.size()-1);
            while(sorted.get(0) != sorted.get(sorted.size()-1)) {

            }
        }

        br.close(); pw.close();
    }

    static void put(ArrayList<Integer> a, int value) {        
        int insertionIndex = -1;
        if(value > a.get(a.size()-1)) insertionIndex = a.size();
        else if(value < a.get(0)) insertionIndex = 0;
        else if(value == a.get(a.size()-1)) insertionIndex = a.size()-1;
        else {
            // int low = 0;
            // int high = a.size() - 1;
            // while(low != high) {
            //     int mid = (low + high) / 2;
            //     if(a.get(mid) == value) {
            //         insertionIndex = mid;
            //         break;
            //     } else if(value < a.get(mid)) {
            //         high = mid - 1;
            //     } else if(value > a.get(mid)) {
            //         low = mid + 1;
            //     }
            // }
            // if(low == high) {
                
            // }
            for(int i = value; i <= a.get(a.size()-1); i++) {
                if(a.indexOf(i) != -1) { insertionIndex = a.indexOf(i); break; }
            }
        }
        a.add(insertionIndex, value);
    }

    static void combine(ArrayList<Integer> logs, int index1, int index2) {
        int sum = logs.get(index1) + logs.get(index2);
        
    }
}
