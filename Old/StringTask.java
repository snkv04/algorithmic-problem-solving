import java.util.*;
import java.io.*;

public class StringTask {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        ArrayList<Character> input = new ArrayList();
        char[] input2 = br.readLine().toLowerCase().toCharArray();
        for (int i = 0; i <= input2.length-1; i++) {
            input.add(input2[i]);
        }
        HashSet<Character> vowels = new HashSet<>();
        vowels.add('a'); vowels.add('e'); vowels.add('i');
        vowels.add('o'); vowels.add('u'); vowels.add('y');
        for (int i = input.size()-1; i >= 0; i--) {
            if (vowels.contains(input.get(i))) input.remove(i);
            else input.add(i, '.');
        }
        for (int i = 0; i <= input.size()-1; i++) {
            pw.print(input.get(i));
        }

        br.close(); pw.close();
    }
}