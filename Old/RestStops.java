import java.util.*;
import java.io.*;

public class RestStops {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("reststops.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("reststops.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        String line[] = br.readLine().split(" ");
        int l = Integer.parseInt(line[0]);
        int n = Integer.parseInt(line[1]);
        int spm = Integer.parseInt(line[2]) - Integer.parseInt(line[3]); // FJ's speed minus Bessie's speed
        ArrayList<Stop> restStops = new ArrayList<Stop>();
        for (int i = 1; i <= n; i++) {
            int[] stopLine = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            restStops.add(new Stop(stopLine[0], stopLine[1]));
        }
        restStops.sort(new Comp());
        // the rest stops are already sorted in order of location

        ArrayList<Stop> importantStops = new ArrayList<Stop>();
        int maxC = Integer.MIN_VALUE;
        for (int i = n-1; i >= 0; i--) {
            if (restStops.get(i).c > maxC) {
                importantStops.add(restStops.get(i));
                maxC = restStops.get(i).c;
            }
        }
        Collections.reverse(importantStops);
        
        int lastStopX = 0;
        long tastiness = 0;
        for (int i = 0; i <= importantStops.size() - 1; i++) {
            tastiness += (long) (importantStops.get(i).x - lastStopX) * spm * importantStops.get(i).c;
            lastStopX = importantStops.get(i).x;
        }
        pw.println(tastiness);

        br.close(); pw.close();
    }

    static class Stop {
        int x;
        int c;

        public Stop(int x, int c) {
            this.x = x;
            this.c = c;
        }

        public String toString() {
            return "(x=" + x + ", c="+c+")";
        }
    }

    static class Comp implements Comparator<Stop> {
        public int compare(Stop s1, Stop s2) {
            return Integer.compare(s1.x, s2.x);
        }
    }
}
