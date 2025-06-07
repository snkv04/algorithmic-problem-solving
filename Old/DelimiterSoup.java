import java.util.*;
import java.io.*;

public class DelimiterSoup {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        Stack<Character> s = new Stack<>();
        char[] brackets = br.readLine().toCharArray();
        for (int i = 0; i <= n-1; i++) {
            if (brackets[i]=='(' || brackets[i]=='[' || brackets[i]=='{') s.add(brackets[i]);
            else if (brackets[i]==')') {
                if (s.isEmpty() || s.peek() != '(') {
                    pw.println(brackets[i]+" "+i);
                    return;
                } else {
                    s.pop();
                }
            } else if (brackets[i]==']') {
                if (s.isEmpty() || s.peek() != '[') {
                    pw.println(brackets[i]+" "+i);
                    return;
                } else {
                    s.pop();
                }
            } else if (brackets[i] == '}') {
                if (s.isEmpty() || s.peek() != '{') {
                    pw.println(brackets[i]+" "+i);
                    return;
                } else {
                    s.pop();
                }
            }
        }
        pw.println("ok so far");
    }
}
