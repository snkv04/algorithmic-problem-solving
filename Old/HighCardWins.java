import java.util.*;
import java.io.*;

public class HighCardWins {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("highcard.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("highcard.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        TreeSet<Integer> bessiesCards = new TreeSet<Integer>();
        for (int i = 1; i <= 2 * n; i++) {
            bessiesCards.add(i);
        }
        TreeSet<Integer> elsiesCards = new TreeSet<Integer>();
        for (int i = 1; i <= n; i++) {
            int line = Integer.parseInt(br.readLine());
            bessiesCards.remove(line);
            elsiesCards.add(line);
        }
        NavigableSet<Integer> reverse = elsiesCards.descendingSet();

        int count = 0;
        for (Integer elsieCard : reverse) {
            if (bessiesCards.higher(elsieCard) == null) {
                bessiesCards.pollFirst();
            } else {
                bessiesCards.remove(bessiesCards.higher(elsieCard));
                count++;
            }
        }
        pw.println(count);

        br.close(); pw.close();
    }
}
