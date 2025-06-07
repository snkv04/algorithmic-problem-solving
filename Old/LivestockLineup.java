import java.util.*;
import java.io.*;


public class LivestockLineup {

    static TreeSet<String> goodPerms = new TreeSet<String>();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("lineup.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("lineup.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        // n is the number of conditions
        String[][] conditions = new String[n][2];
        for (int i = 0; i <= n-1; i++) {
            String[] split = br.readLine().split(" must be milked beside ");
            conditions[i][0] = split[0];
            conditions[i][1] = split[1];
        }
        // System.out.println(conditions);

        String[] firstPerm = {"Beatrice", "Belinda", "Bella", "Bessie", "Betsy", "Blue", "Buttercup", "Sue"};
        generatePermutations(firstPerm, 0, conditions); // adds to arraylist of good permutations

        // System.out.println(goodPerms + "\n");
        // goodPerms.sort(new MyComp());
        for (String cow: goodPerms.first().split(" ")) {
            pw.println(cow);
        }

        br.close(); pw.close();
    }

    static void generatePermutations (String[] a, int fixedIndex, String[][] conditions) {
        if (fixedIndex == a.length - 1) {
            // System.out.println(Arrays.toString(a));
            checkPermutation(a, conditions);
        }
        for (int i = fixedIndex; i <= a.length - 1; i++) {
            String temp = a[i];
            a[i] = a[fixedIndex];
            a[fixedIndex] = temp;
            generatePermutations(a, fixedIndex+1, conditions);
            temp = a[i];
            a[i] = a[fixedIndex];
            a[fixedIndex] = temp;
        }
    }

    static void checkPermutation (String[] perm, String[][] conditions) {
        int count = 0;
        for(int i = 0; i <= perm.length - 2; i++) {
            // counts how many conditions were matched
            boolean matchedCondition = false;
            for (int j = 0; j <= conditions.length - 1; j++) {
                // checks if a pair within the array matched any condition
                if ((perm[i].equals(conditions[j][0]) && perm[i+1].equals(conditions[j][1])) ||
                (perm[i].equals(conditions[j][1]) && perm[i+1].equals(conditions[j][0]))) {
                    matchedCondition = true;
                    break;
                }
            }
            if (matchedCondition) count++;
        }

        if (count == conditions.length) {
            String toString = perm[0];
            for (int i = 1; i <= perm.length - 1; i++) {
                toString += " " + perm[i];
            }
            goodPerms.add(toString);
        }
    }
}

// class MyComp implements Comparator<String> {
//     public int compare(String perm1, String perm2) {
//         return perm1.compareToIgnoreCase(perm2);
//     }
// }