import java.util.*;
import java.io.*;

public class CreatingStrings {

    static TreeSet<String> ts = new TreeSet<String>();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String s = br.readLine();
        generatePermutations(s, 0);
        pw.println(ts.size());
        Iterator it = ts.iterator();
        
        for (; it.hasNext();) {
            pw.println(it.next());
        }

        br.close(); pw.close();
    }

    static void generatePermutations(String s, int fixedIndex) {
        if (fixedIndex == s.length() - 1) {
            ts.add(s);
        }

        for (int i = fixedIndex; i <= s.length() - 1; i++) {
            char[] cArray = s.toCharArray();
            char temp = cArray[i];
            cArray[i] = cArray[fixedIndex];
            cArray[fixedIndex] = temp;
            generatePermutations(new String(cArray), fixedIndex+1);
            temp = cArray[i];
            cArray[i] = cArray[fixedIndex];
            cArray[fixedIndex] = temp;
            s = new String(cArray);
        }
    }
}
