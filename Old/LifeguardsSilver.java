import java.util.*;
import java.io.*;

public class LifeguardsSilver {
    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("lifeguards.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("lifeguards.out")));

        int n = Integer.parseInt(br.readLine());
        Lifeguard[] lifeguards = new Lifeguard[2*n];
        for (int i = 0; i <= n-1; i++) {
            String[] line = br.readLine().split(" ");
            int start = Integer.parseInt(line[0]);
            int end = Integer.parseInt(line[1]);
            // use 2*i and 2*i+1 as the indices to fill in the array, then sort
            lifeguards[2*i] = new Lifeguard(i, start, 1);
            lifeguards[2*i+1] = new Lifeguard(i, end, -1);
        }
        Arrays.sort(lifeguards, new Comp());
        // pw.println(Arrays.toString(lifeguards));

        // each lifeguard has a start and end time
        TreeSet<Integer> currPresent = new TreeSet<Integer>();
        int[] alonePerLifeguard = new int[n];
        int totalCovered = 0;
        currPresent.add(lifeguards[0].id);
        int lastTime = lifeguards[0].time; // has to have been added
        for (int i = 1; i <= 2*n-1; i++) {
            if (currPresent.size() == 1) {
                alonePerLifeguard[currPresent.first()] += lifeguards[i].time - lastTime;
            }
            if (!currPresent.isEmpty()) {
                totalCovered += lifeguards[i].time - lastTime;
            }

            if (lifeguards[i].addOrRemove==1) {
                currPresent.add(lifeguards[i].id);
            } else if (lifeguards[i].addOrRemove == -1) {
                currPresent.remove(lifeguards[i].id);
            }

            lastTime = lifeguards[i].time;
        }
        // pw.println(Arrays.toString(alonePerLifeguard));

        int min = Integer.MAX_VALUE;
        for (int timeAlone:alonePerLifeguard) min = Math.min(min, timeAlone);
        pw.println(totalCovered-min);

        br.close(); pw.close();

        // basically, we want to find the largest time covered when one lifeguard gets fired.
        // this means we want to find the minimum time that any one lifeguard spends working
        // alone, and subtract that from the total amount of time covered. so, we set up a class
        // that represents an endpoint of a lifeguard's shift, either start or end endpoint,
        // ensuring that we can access its time, actual lifeguard it's connected to, and whether
        // it's a start or end. then, we make an array that is twice the length of the number of
        // lifeguards in order to store all of these objects, and sort the array by the time value
        // of each element. we also maintain a set of the currently working lifeguards for the
        // upcoming for loop. then, for each object, we check if at that time there is only
        // one lifeguard working. if it is, then in an array that keeps track of how many
        // units of time each lifeguard spends alone, we increment that specific lifeguard's alone
        // time by the current time minus the time of the last time value we checked. also, if
        // the set of currently working lifeguards is not empty, we increment the total
        // sum of time that is covered by lifeguards. now, if the current lifeguard endpoint
        // is a start, we add the lifeguard associated with the object to the array, and
        // vice versa if it's an end of a shift. then, we find the minimum alone time worked
        // by any lifeguard, and subtract it from the total covered time.
        // also, by the way, since the intervals are represented by endpoints, when represented
        // in an array, the array is used in such a way that the interval does not include
        // the end point, i.e. [1,4] fills up the 3 spaces 1, 2, and 3 in an array. also, instead
        // of going and checking every square of time, the algorithm "jumps" from endpoint to
        // endpoint in chronological order.
    }

    static class Lifeguard {
        int id, time, addOrRemove;

        public Lifeguard(int id, int time, int addOrRemove) {
            this.id = id;
            this.time = time;
            this.addOrRemove = addOrRemove;
        }

        public String toString() {
            return "(id="+id+",time="+time+",addOrRemove="+(addOrRemove==1?"add":"remove)");
        }
    }

    static class Comp implements Comparator<Lifeguard> {
        public int compare(Lifeguard l1, Lifeguard l2) {
            return Integer.compare(l1.time, l2.time);
        }
    }
}
