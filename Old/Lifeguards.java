import java.io.*;

public class Lifeguards {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("lifeguards.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("lifeguards.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        
        int n = Integer.parseInt(br.readLine());
        Lifeguard[] lgs = new Lifeguard[n];
        for(int i = 0; i <= n-1; i++) {
            String[] split = br.readLine().split(" ");
            lgs[i] = new Lifeguard(Integer.parseInt(split[0]), Integer.parseInt(split[1]));
        }

        // have array of length 1000 to keep track of each time unit, numbered 1-1000
        // actually numbered 0-999, each interval's end is not included
        // fill it in for the lifeguards available, then check how many lifeguards are covering each time unit
        // for each lifeguard, check how many shifts would change to 0 if they were fired
        // find the minimum of this
        int[] guardsPerTime = new int[1000000];
        for(Lifeguard lifeguard: lgs) {
            for(int i = lifeguard.start; i <= lifeguard.end-1; i++) {
                guardsPerTime[i]++;
            }
        }

        int totalCovered = 0;
        for(int i = 0; i <= 999999; i++) {
            if (guardsPerTime[i] != 0) {
                totalCovered++;
            }
        }
        int minLost = Integer.MAX_VALUE;
        for(int i = 0; i <= lgs.length - 1; i++) {
            int lost = 0;
            for(int j = lgs[i].start; j <= lgs[i].end - 1; j++) {
                if (guardsPerTime[j] == 1) {
                    lost++;
                }
            }
            minLost = Math.min(minLost, lost);
        }

        pw.println(totalCovered - minLost);

        br.close(); pw.close();
    }
}

class Lifeguard {
    int start;
    int end;

    public Lifeguard(int start, int end) {
        this.start = start;
        this.end = end;
    }
}