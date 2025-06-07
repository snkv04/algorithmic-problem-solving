import java.util.*;
import java.io.*;

public class LivingSequence {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        HashMap<Integer, String> map = new HashMap();
        map.put(0, "0");
        map.put(1, "1");
        map.put(2, "2");
        map.put(3, "3");
        map.put(4, "5");
        map.put(5, "6");
        map.put(6, "7");
        map.put(7, "8");
        map.put(8, "9");
        for (int i = 1; i <= t; i++) {
            long k = Long.parseLong(br.readLine());

            // literally just converts k to the base 9 numeral system
            ArrayList<Integer> reverseDigits = new ArrayList();
            while (k > 0) {
                reverseDigits.add((int)(k % 9));
                k /= 9;
            }

            // maps the base 9 digits 012345678 to 012356789
            String result = "";
            for (int j = reverseDigits.size()-1; j >= 0; j--) {
                result += map.get(reverseDigits.get(j));
            }
            pw.println(result);
        }

        br.close(); pw.close();
    }
}
