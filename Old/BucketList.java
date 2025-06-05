import java.util.*;
import java.io.*;

public class BucketList {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("blist.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("blist.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        TreeSet<Cow> cows = new TreeSet<Cow>(new MyComp());
        for (int i = 0; i <= n-1; i++) {
            String[] split = br.readLine().split(" ");
            int s = Integer.parseInt(split[0]);
            int e = Integer.parseInt(split[1]);
            int b = Integer.parseInt(split[2]);
            cows.add(new Cow(s, e, b));
        }
        
        // sort all cows by their start
        // have a variable for currentBuckets and maxBuckets
        // have an arraylist of current cows milking
        // loop through the cows
        // each cow, add it to the current milking array
        // also, conduct a check
            // the check consists of seeing how many of the cows in the currentMilking array are done
            // for each cow that is done, reduce the currentBuckets and remove the cow
        // then, add its buckets to currentBuckets
        // check if maxBuckets is less than current; if so, increase maxBuckets
        ArrayList<Cow> currentMilking = new ArrayList<Cow>();
        int currentBuckets = 0;
        int maxBuckets = 0;
        Iterator it = cows.iterator();
        for (; it.hasNext();) {
            Cow currentCow = (Cow)it.next();
            int newStart = currentCow.start;
            for (int i = currentMilking.size() - 1; i >= 0; i--) {
                if (currentMilking.get(i).end < newStart) {
                    currentBuckets -= currentMilking.get(i).buckets;
                    currentMilking.remove(currentMilking.get(i));
                }
            }

            currentMilking.add(currentCow);
            currentBuckets += currentCow.buckets;
            maxBuckets = Math.max(maxBuckets, currentBuckets);
        }

        pw.println(maxBuckets);

        br.close(); pw.close();
    }

    static class Cow {
        int start;
        int end;
        int buckets;

        public Cow (int start, int end, int buckets) {
            this.start = start;
            this.end = end;
            this.buckets = buckets;
        }
    }

    static class MyComp implements Comparator<Cow> {
        public int compare (Cow cow1, Cow cow2) {
            return Integer.compare(cow1.start, cow2.start);
        }
    }
}
