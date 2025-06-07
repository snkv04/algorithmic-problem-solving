import java.util.*;
import java.io.*;

public class WhereAmI {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("whereami.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("whereami.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        br.readLine();
        String mailboxes = br.readLine();
        
        // loop over values of k from 1 to n
        // for each value of k, check all substrings of that length
        // if any substring of that length is equal to a previous substring of that length, increment k
        // as soon as k gives substrings that are all unique from the original string, return k
        ArrayList<String> substrings = new ArrayList<String>();
        boolean kWorks = true;
        int minK = 0;
        for(int k = 1; k <= mailboxes.length(); k++) {
            // testing this value of k
            for (int i = 0; i <= mailboxes.length() - k; i++) {
                if (substrings.contains(mailboxes.substring(i, i+k))) {
                    kWorks = false;
                    substrings.clear();
                    break;
                }
                substrings.add(mailboxes.substring(i, i+k));
            }
            
            if (kWorks) {
                minK = k;
                break;
            } else {
                kWorks = true; // continue through the outer loop
            }
        }

        pw.println(minK);

        br.close(); pw.close();
    }
}
