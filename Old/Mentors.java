import java.util.*;
import java.io.*;

public class Mentors {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int k = sc.nextInt();
        Mentor[] r = new Mentor[n];
        for (int i = 0; i <= n-1; i++) r[i] = new Mentor(i, sc.nextInt());
        int[] numQuarrels = new int[n];
        for (int i = 1; i <= k; i++) {
            int a = sc.nextInt()-1;
            int b = sc.nextInt()-1;
            if (r[a].rating > r[b].rating) {
                numQuarrels[a]++;
            }
            if (r[b].rating > r[a].rating) numQuarrels[b]++;
        }
        Arrays.sort(r);

        int last = -1;
        int[] answers = new int[n];
        answers[r[0].id] = 0;
        for (int i = 1; i <= n-1; i++) {
            if (r[i].rating > r[i-1].rating) {
                last = i-1;
            }

            // if (last!=-1) {
                int mentorable = last+1;
                answers[r[i].id] = mentorable - numQuarrels[r[i].id];
            // } else {
            //     answers[r[i].id] = 0;
            // }
        }
        for (int ans : answers) pw.print(ans + " ");

        sc.close(); pw.close();
    }

    static class Mentor implements Comparable<Mentor> {
        int id, rating;

        public Mentor(int id, int rating) {
            this.id = id;
            this.rating = rating;
        }

        public int compareTo(Mentor other) {
            return Integer.compare(this.rating, other.rating);
        }
    }
}
