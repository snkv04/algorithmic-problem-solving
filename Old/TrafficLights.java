import java.util.*;
import java.io.*;

public class TrafficLights {
    static TreeMap<Integer, Integer> multiset; // represents the (lengths of) gaps between lights

    public static void main(String[] args) throws IOException{
        // //get the two first inputs
        // //make a set with two values (0, and the length of the street) already in it
        // //add all the lights to the treeset
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // String line1 = br.readLine();
        // int x = Integer.parseInt(line1.split(" ")[0]);
        // int n = Integer.parseInt(line1.split(" ")[1]);
        // TreeSet<Integer> lights = new TreeSet<Integer>();
        // lights.add(0); lights.add(x);
        // String[] line2 = br.readLine().split(" ");
        // for(int i = 0; i<n; i++){
        //     lights.add(Integer.parseInt(line2[i]));
        // }

        // //find a max length in the current treeset
        // //add that to an output stack
        // int maxDist = 0;
        // int prevLight = 0;
        // TreeSet<Integer> lights2 = (TreeSet<Integer>)lights.clone();
        // for(int light: lights){
        //     maxDist = Math.max(maxDist, light - prevLight);
        //     prevLight = light;
        // }
        // Stack<Integer> outputStack = new Stack<Integer>();
        // outputStack.push(maxDist);

        // //for loop, n-1 times:
        // //remove the most recent item in line2 array from the treeset, and
        // //      compute the maximum between the new gap and the biggest gap
        // for(int i = n-1; i>=1; i--){
        //     int light = Integer.parseInt(line2[i]);
        //     lights.remove(light);
        //     maxDist = Math.max(maxDist, lights.higher(light) - lights.lower(light));
        //     outputStack.push(maxDist);
        // }

        // // compiling the output into a string
        // // 1 String output = "";
        // for(int i=1; i<=n; i++){
        //     // 2 output += outputStack.pop() + " ";
        //     System.out.print(outputStack.pop() + " ");
        // }
        // // 3 System.out.println(output);

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int x = Integer.parseInt(line[0]);
        int n = Integer.parseInt(line[1]);
        int[] p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        TreeMap<Integer, Integer> gaps = new TreeMap<Integer, Integer>(); // key is gap start, value is gap length
        gaps.put(0, x);
        multiset = new TreeMap<Integer, Integer>();
        add(x);
        for (int i = 0; i <= n-1; i++) {
            int light = p[i];
            int split_gap_start = gaps.floorKey(light);
            int split_gap_length = gaps.get(split_gap_start);
            gaps.put(light, split_gap_start + split_gap_length - light);
            gaps.put(split_gap_start, light - split_gap_start); // automatically removes the gap being split
            remove(split_gap_length);
            add(split_gap_start + split_gap_length - light);
            add(light - split_gap_start);
            pw.print(multiset.lastKey() + " ");
        }

        br.close(); pw.close();
    }

    public static void add(int n) {
        // adds a stretch of road's length to the multiset
        if (multiset.containsKey(n)) multiset.put(n, multiset.get(n) + 1);
        else multiset.put(n, 1);
    }

    public static void remove(int n) {
        multiset.put(n, multiset.get(n) - 1);
        if (multiset.get(n) == 0) multiset.remove(n);
    }
}
