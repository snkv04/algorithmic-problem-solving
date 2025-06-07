import java.util.*;
import java.io.*;

public class StrongPassword {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            // char[] s = br.readLine().toCharArray();
            // int m = Integer.parseInt(br.readLine());
            // char[] l = br.readLine().toCharArray();
            // char[] r = br.readLine().toCharArray();
            int[] s = Arrays.stream(br.readLine().split("")).mapToInt(Integer::parseInt).toArray();
            int m = Integer.parseInt(br.readLine());
            int[] l = Arrays.stream(br.readLine().split("")).mapToInt(Integer::parseInt).toArray();
            int[] r = Arrays.stream(br.readLine().split("")).mapToInt(Integer::parseInt).toArray();
            // out of all the digits numerically between l[i] and r[i], latestEarliest[i]
            // describes the latest index in the database of the earliest appearances of each
            // of those digits
            int[] latestEarliest = new int[m+1];
            latestEarliest[0]=-1;
            boolean good = false;
            for (int j=1; j<=m && !good; j++) {
                if (latestEarliest[j-1]==s.length-1) {
                    good=true;
                    break;
                }
                latestEarliest[j] = -1;
                for (int k = l[j-1]; k <= r[j-1] && !good; k++) {
                    for (int letter = latestEarliest[j-1]+1; letter <= s.length-1 && !good; letter++) {
                        if (s[letter] == k) {
                            latestEarliest[j] = Math.max(latestEarliest[j], letter);
                            break;
                        }
                        if (letter==s.length-1) {
                            good = true;
                            break;
                        }
                    }
                }
                // if (earliest[j]==Integer.MAX_VALUE) {
                //     good = true;
                //     break;
                // }
            }
            pw.println(good?"YES":"NO");
        }

        br.close(); pw.close();

        // holy shit, consider edge cases dumbass. the importance of considering
        // all cases cannot be understated.
        // basically, we want to find at least one password that is "between"
        // l and r (meaning that each element is numerically between, inclusive,
        // the corresponding elements of l and r) which is not a subsequence of the
        // database string. for each character of l/r, or in other words for each of
        // the m indices, we check all possible digits within the bounds given by l
        // and r, and to do this we look at the earliest occurrence of each one and
        // find the latest of these (as using this digit will give the least chance
        // of the rest of the string being contained within the database, while also
        // not missing any potential substrings by using the earliest occurrence).
        // then, for the next character in our password, we start at that latestIndex+1
        // and do the same thing. what happens is that we look at each character
        // individually, checking all possible values for that character, and in
        // each position using the optimal character that makes it most likely that
        // the whole password won't be in the database. if at any point, for any
        // character index and for any value for that character, we cannot find
        // a next value, then any password beginning with the characters chosen so
        // far (including that last one) will not be contained in the database (as
        // even that prefix is not contained). now, if at any point, the latest
        // earliest character for a digit index is the very end of the database string
        // while there are still more characters to consider, then they cannot
        // obviously be found and any passwords with that prefix won't be in the
        // database. under those conditions, the answer would be yes, otherwise it
        // would be no.
    }
}
