import java.util.*;
import java.io.*;

public class Photoshoot {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader("photo.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("photo.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] bList = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        // bList.length = n-1
        
        // for loop where i goes from 1 to n
        // fill out list, if it's a valid permutation then return
        // don't need to compare with other permutations because starting at lexicographically lowest permutation
        // so, first permutation that works will be lexicographically lowest
        ArrayList<Integer> aList = new ArrayList<Integer>();
        for (int i = 1; i <= n; i++) {
            aList.add(i);
            for (int j = 1; j <= n-1; j++) {
                int newValue = bList[j-1] - aList.get(j-1);
                if(newValue >= 1 && newValue <= n && !aList.contains(newValue)) {
                    aList.add(bList[j-1] - aList.get(j-1));
                } else {
                    aList.clear();
                    break;
                }
            }
            if (aList.size() == n) {
                break;
            } else {
                aList.clear();
            }
        }

        pw.print(aList.get(0));
        for(int i = 1; i <= n-1; i++) {
            pw.print(" " + aList.get(i));
        }

        br.close(); pw.close();
    }
}

// class MyComp implements Comparator<ArrayList<Integer>> {
//     public int compare(ArrayList<Integer> list1, ArrayList<Integer> list2) {
//         int length = Math.min(list1.size(), list2.size());
//         for(int i = 0; i <= length-1; i++) {
//             if (list1.get(i) > list2.get(i)) {
//                 return -1;
//             } else if (list2.get(i) > list1.get(i)) {
//                 return 1;
//             }
//         }

//         if (list1.size() > list2.size()) return -1;
//         else if (list1.size() < list2.size()) return 1;
//         else return 0;
//     }
// }