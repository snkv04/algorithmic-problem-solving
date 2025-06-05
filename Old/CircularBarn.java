// import java.util.*;
// import java.io.*;

// public class CircularBarn {
//     public static void main(String[] args) throws Exception{
//         BufferedReader br = new BufferedReader(new FileReader("cbarn.in"));
//         PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));
 
//         int n = Integer.parseInt(br.readLine());
//         ArrayList<Integer> capacityList = new ArrayList<Integer>();
//         for(int i = 0; i <= n - 1; i++) {
//             capacityList.add(Integer.parseInt(br.readLine()));
//         }
        
//         // for loop to change the order of the arraylist each time
//         // at end of each loop, check if total distance traveled is minimum or no
//         // in each loop, find the total distance traveled by the cows by multiplying the 
//         int minTotalDist = Integer.MAX_VALUE;
//         for(int i = 0; i < n; i++) {
//             int totalDist = 0;
//             for(int j = 1; j < n; j++) {
//                 int dist = j;
//                 // if (j > n/2) {
//                 //     dist = n-j;
//                 // }
//                 totalDist += dist * capacityList.get(j);
//             }
//             minTotalDist = Math.min(minTotalDist, totalDist);
//             capacityList.add(capacityList.remove(0)); // move the value at beginning of rList to end
//         }

//         pw.print(minTotalDist);

//         br.close(); pw.close();
//     }
// }

import java.util.*;
import java.io.*;

public class CircularBarn {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("cbarn.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));

        int n = Integer.parseInt(br.readLine());
        int[] r = new int[n];
        for (int i = 0; i <= n-1; i++) {
            r[i] = Integer.parseInt(br.readLine());
        }

        int minDist = Integer.MAX_VALUE;
        for (int i = 0; i <= n-1; i++) {
            int dist = 0;
            for (int j = 1; j <= n-1; j++) {
                dist += j * r[(i+j)%n];
            }
            minDist = Math.min(minDist, dist);
        }
        pw.println(minDist);

        br.close(); pw.close();
    }
}