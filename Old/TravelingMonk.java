import java.util.*;

public class TravelingMonk {

    // Function to find the location based on the pref_h and pref_t arrays
    public static double findLoc(List<Integer> prefH, List<Integer> prefT, double time) {
        int l = 0, r = prefH.size() - 1, idx = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (prefT.get(mid) <= time) {
                idx = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        double loc = prefH.get(idx);
        double remaining = time - prefT.get(idx);
        loc += remaining / (prefT.get(idx + 1) - prefT.get(idx)) * (prefH.get(idx + 1) - prefH.get(idx));
        return loc;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Read the input values
        int a = sc.nextInt();
        int d = sc.nextInt();
        
        // Prepare lists to store the prefix locations and times
        List<Integer> prefALoc = new ArrayList<>();
        List<Integer> prefATime = new ArrayList<>();
        List<Integer> prefDLoc = new ArrayList<>();
        List<Integer> prefDTime = new ArrayList<>();

        prefALoc.add(0);
        prefATime.add(0);
        
        for (int i = 1; i <= a; ++i) {
            int dist = sc.nextInt();
            int time = sc.nextInt();
            prefALoc.add(prefALoc.get(prefALoc.size() - 1) + dist);
            prefATime.add(prefATime.get(prefATime.size() - 1) + time);
        }

        prefDLoc.add(0);
        prefDTime.add(0);
        
        for (int i = 1; i <= d; ++i) {
            int dist = sc.nextInt();
            int time = sc.nextInt();
            prefDLoc.add(prefDLoc.get(prefDLoc.size() - 1) + dist);
            prefDTime.add(prefDTime.get(prefDTime.size() - 1) + time);
        }

        // Binary search for the correct time
        double l = 0, r = Math.min(prefATime.get(a), prefDTime.get(d));
        
        // Perform the binary search to find the location
        for (int i = 1; i <= 60; ++i) {
            double mid = (l + r) / 2.0;
            double heightA = findLoc(prefALoc, prefATime, mid);
            double heightD = prefALoc.get(a) - findLoc(prefDLoc, prefDTime, mid);
            
            if (heightA < heightD) {
                l = mid;
            } else {
                r = mid;
            }
        }

        // Output the final result
        System.out.println(l);
    }
}