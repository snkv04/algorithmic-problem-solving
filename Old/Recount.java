import java.util.*;
import java.io.*;

public class Recount {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        Multiset votes = new Multiset();
        while (true) {
            String vote = br.readLine();
            if (vote.equals("***")) break;

            votes.add(vote);
        }

        int max = -1;
        int num = 0;
        String maxCandidate = "";
        while (!votes.mset.isEmpty()) {
            if (votes.mset.firstEntry().getValue() > max) {
                max = votes.mset.firstEntry().getValue();
                maxCandidate = votes.mset.firstKey();
                num = 1;
            } else if (votes.mset.firstEntry().getValue() == max) {
                num++;
            }
            votes.mset.pollFirstEntry();
        }

        if (num==1) pw.println(maxCandidate);
        else pw.println("Runoff!");

        br.close(); pw.close();
    }

    // // // //

    static class Multiset { // ordered multiset
        TreeMap<String, Integer> mset = new TreeMap<>();

        public void add(String x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(String x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }
    }
}
