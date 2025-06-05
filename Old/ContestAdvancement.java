import java.util.*;
import java.io.*;

public class ContestAdvancement {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] asdf = br.readLine().split(" ");
        int n = Integer.parseInt(asdf[0]), total = Integer.parseInt(asdf[1]), schoolLimit = Integer.parseInt(asdf[2]);
        int[] schoolCounts = new int[n+1];
        TreeSet<Team> overLimit = new TreeSet<>(Comparator.comparingInt(o -> o.rank)),
            chosen = new TreeSet<>(Comparator.comparingInt(o -> o.rank));
        int numChosen = 0;
        for (int i = 1; i <= n; i++){
            asdf = br.readLine().split(" ");
            int id = Integer.parseInt(asdf[0]), school = Integer.parseInt(asdf[1]);
            if (schoolCounts[school] >= schoolLimit) {
                overLimit.add(new Team(i, id, school));
            } else {
                numChosen++;
                chosen.add(new Team(i, id, school));
                schoolCounts[school]++;
                if (numChosen == total) break;
            }
        }

        for (Team tm : overLimit) {
            if (numChosen == total) break;
            chosen.add(tm);
            numChosen++;
        }

        for (Team tm : chosen) {
            pw.println(tm.id);
        }
    }

    static class Team {
        int rank, id, school;

        public Team(int rank, int id, int school) {
            this.rank = rank;
            this.id = id;
            this.school = school;
        }
    }
}