import java.util.*;
import java.io.*;

public class Alchemy {
    static int[] amts;
    static ArrayList<Integer>[] recipes;
    static int n, k;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        n = sc.nextInt();
        amts = new int[n];
        for (int i = 0; i <= n-1; i++) amts[i] = sc.nextInt();
        k = sc.nextInt();
        recipes = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) recipes[i]=new ArrayList<Integer>();
        for (int i = 1; i <= k; i++) {
            int l = sc.nextInt() - 1;
            int m = sc.nextInt();
            for (int j = 1; j <= m; j++) recipes[l].add(sc.nextInt()-1);
        }
        // for (int i = 0; i <= n-1; i++) pw.println("i="+i+", and recipces = "+recipes[i]);

        // obviously, if there are no recipes to make metal N, then it can never be made
        // the only recipes that matter are the ones that make metal N, the ones that make
        // its constituents, the ones that make the constituents of that, etc.
        while (makeMetal(n-1)) {
            amts[n-1]++;
        }
        pw.println(amts[n-1]);

        sc.close(); pw.close();

        // idk how this solution actually works, since the recipe tree of metal 100
        // can potentially be of size 2^99 (which it actually is in test case 5); this
        // should ESPECIALLY not work if there are no units of any metal except for metal
        // 1, which means that the algorithm has to recurse down the entire tree every
        // single time it tries to make one unit of metal N
    }

    static boolean makeMetal(int metal) {
        // look at each metal in recipe
        // if it's available, then subtract one from that metal and look at next metal
        // if there's none of it and it has a recipe, then make that
        // if there's none of it and there's no recipe, then nothing can be made
        if (amts[metal] > 0 && metal != n-1) {
            amts[metal]--;
            return true;
        }
        // there is none of the current metal
        if (recipes[metal].isEmpty()) {
            return false;
        }

        // ANDing the previous results with each current one (each metal in the recipe)
        // ensures that either all of them work or none of them do
        boolean works = true;
        for (int constituent : recipes[metal]) {
            works = works && makeMetal(constituent);
        }
        return works;
    }


}
