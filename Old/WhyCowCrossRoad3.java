import java.util.*;
import java.io.*;

public class WhyCowCrossRoad3 {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader("cowqueue.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cowqueue.out")));

        int n = Integer.parseInt(br.readLine());
        String[] lines = new String[n];
        for(int i = 0; i <= n-1; i++) {
            lines[i] = br.readLine();
        }
        Arrays.sort(lines, new MyComp());

        int[] starts = new int[n];
        int[] durations = new int[n];
        for(int i = 0; i <= n-1; i++) {
            starts[i] = Integer.parseInt(lines[i].split(" ")[0]);
            durations[i] = Integer.parseInt(lines[i].split(" ")[1]);
        }

        // int previousEnd = 0;
        int totalTime = 0;
        // for loop to go through each cow
        // find the latest starting for each cow

        // at end of loop, set previous end to be latestStart + duration
        for(int i = 0; i < n; i++) {
            // int latestStart = Math.max(previousEnd, starts[i]);
            int latestStart = Math.max(totalTime, starts[i]);
            totalTime = latestStart + durations[i];
        }
        pw.print(totalTime);

        br.close(); pw.close();
    }

    static class MyComp implements Comparator<String> {
        public int compare(String s1, String s2) {
            return Integer.compare(Integer.parseInt(s1.split(" ")[0]), Integer.parseInt(s2.split(" ")[0]));
        }
    }
}