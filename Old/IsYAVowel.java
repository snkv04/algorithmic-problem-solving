import java.util.*;
import java.io.*;

public class IsYAVowel {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        HashSet<Character> vowels = new HashSet<>();
        char[] _vowels = "aeiou".toCharArray();
        for (int i = 0; i <= 4; i++) vowels.add(_vowels[i]);

        char[] s = br.readLine().toCharArray();
        int c1 = 0, c2 = 0;
        for (int i = 0; i <= s.length-1; i++) {
            if (vowels.contains(s[i])) c1++;
            if (s[i]=='y') c2++;
        }
        pw.println(c1+" "+(c1+c2));
    }
}

// import java.util.*;
// import java.io.*;

// public class Template {
//     static BufferedReader br;
//     static PrintWriter pw;

//     public static void main(String[] args) throws IOException {
//         br = new BufferedReader(new InputStreamReader(System.in));
//         pw = new PrintWriter(System.out);

//         solve();

//         br.close(); pw.close();
//     }

//     static void solve() throws IOException {
//         //
//     }
// }