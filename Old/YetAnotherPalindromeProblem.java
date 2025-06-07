import java.util.*;
import java.io.*;

public class YetAnotherPalindromeProblem {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i=1; i<=t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            boolean works = false;
            for (int j = 0; j <= n-3 && !works; j++) {
                for (int k = j+2; k <= n-1; k++) {
                    if (a[j]==a[k]) {
                        works = true; break;
                    }
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();

        // observe that if we can make a palindrome of length longer than 3 by removing
        // characters, then we can remove more characters and make a palindrome of length 3.
        // this means we don't have to look for palindromes of length longer than 3, only
        // of length 3. this is easy, as all we need is for two characters that are 2 away
        // or farther than that to be equal, as whatever is in the middle (regardless of if
        // it is equal to the endpoints of the palindrome) doesn't matter. then we can
        // remove everything other than the endpoints and some random single character
        // between them, and we have a palindrome.
    }
}
