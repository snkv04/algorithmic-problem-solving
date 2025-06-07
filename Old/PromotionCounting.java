import java.util.*;
import java.io.*;

public class PromotionCounting {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("promote.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("promote.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        Division[] divisions = new Division[4];
        for(int i = 0; i <= 3; i++) {
            String[] split = br.readLine().split(" ");
            divisions[i] = new Division(Integer.parseInt(split[0]), Integer.parseInt(split[1]));
        }

        // going down from plat, subtract the beginning from the end and add that difference
        // to each of the division movements before it
        int[] moved = new int[3];
        for(int i = 3; i >= 1; i--) {
            int difference = divisions[i].end - divisions[i].start;
            for(int j = 0; j <= i-1; j++) {
                moved[j] += difference;
            }
        }

        for(int i = 0; i <= 2; i++) { pw.println(moved[i]); }

        br.close(); pw.close();
    }
}

class Division {
    int start = 0;
    int end = 0;

    public Division(int start, int end) {
        this.start = start;
        this.end = end;
    }
}
