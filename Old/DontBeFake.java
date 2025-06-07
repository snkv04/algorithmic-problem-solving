import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class DontBeFake {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        ArrayList<Event>[] seconds = new ArrayList[86400]; for (int i = 0; i < 86400; i++) seconds[i] = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int[] events = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            for (int j = 1; j < events.length; j++) {
                seconds[events[j]].add(new Event(i, j%2==0));
            }
        }

        HashSet<Integer> currPeople = new HashSet<>();
        int max = 0;
        for (int i = 0; i < 86400; i++) {
            for (Event e : seconds[i]) {
                if (!e.ending) {
                    currPeople.add(e.person);
                }
            }
            max = Math.max(max, currPeople.size());
            for (Event e : seconds[i]) {
                if (e.ending) {
                    currPeople.remove(e.person);
                }
            }
        }

        int times = 0;
        currPeople = new HashSet<>();
        for (int i = 0; i < 86400; i++) {
            for (Event e : seconds[i]) {
                if (!e.ending) {
                    currPeople.add(e.person);
                }
            }
            if (currPeople.size() == max) {
                times++;
            }
            for (Event e : seconds[i]) {
                if (e.ending) {
                    currPeople.remove(e.person);
                }
            }
        }

        pw.println(max);
        pw.println(times);
    }

    static class Event {
        int person;
        boolean ending;

        public Event(int person, boolean ending) {
            this.person = person;
            this.ending = ending;
        }
    }
}
