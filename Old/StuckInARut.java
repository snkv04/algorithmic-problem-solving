// import java.util.*;

// public class StuckInARut {
//     public static void main(String[] args){
//         Scanner sc = new Scanner(System.in);
//         int cows = Integer.parseInt(sc.nextLine());
//         ArrayList<Cow> cowList = new ArrayList<Cow>();
//         for(int i = 1; i <= cows; i++) {
//             String[] values = sc.nextLine().split(" ");
//             cowList.add(new Cow(values[0], new int[] {Integer.parseInt(values[1]), Integer.parseInt(values[2])}));
//         }
//         sc.close();
//     }
    
//     public boolean gameEnded(ArrayList<Cow> cowList){
//         return false;
//         //should return true if no more intersections iwll occur
//     }

//     public boolean willIntersect(Cow cow1, Cow cow2){
//         return true;
//         //should return true if a cow will stop the other one
//     }
// }

// //constructor shoudl take in direction and starting point
// //attributes should be direction, staritng point, andcurrrentp oitn

// //have arrraylist of arrays with length 2, representing the eaten plots
// //have method in cow class to move turn, going in direction and updating the current pot
// //return the eaten plot
// class Cow{
//     private String direction;
//     private int[] start;
//     public int[] current;

//     public Cow(String direction, int[] start){
//         this.direction = direction;
//         this.start = start;
//         this.current = start.clone();
//     }

//     public int[] move() {
//         int x = current[0];
//         int y = current[1];
//         if (direction == "N") {
//             current[1] = y+1;
//         } else {
//             current[0] = x+1;
//         }
//         int[] old = {x, y};
//         return old;
//     }
// }

import java.util.*;
import java.io.*;

public class StuckInARut {
    static Cow[] cows;
    static ArrayList<Cow> active;
    static TreeSet<Rut> ruts;
    static int[] distances;
    
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        cows = new Cow[n];
        active = new ArrayList<Cow>();
        for (int i = 0; i <= n-1; i++) {
            char direction = sc.next().charAt(0);
            int x = sc.nextInt();
            int y = sc.nextInt();
            Cow c = new Cow(i, x, y, direction);
            cows[i] = c;
            active.add(c);
        }

        TreeSet<Integer> times = new TreeSet();
        for (int i = 0; i <= n-1; i++) {
            for (int j=i+1; j<=n-1; j++) {
                // calculates the time of potential intersection
                if (cows[i].direction=='E' && cows[j].direction=='E'
                    || cows[i].direction=='N' && cows[j].direction=='N') {

                    continue;
                }

                Cow right, up;
                if (cows[i].direction=='E') {
                    right = cows[i];
                    up = cows[j];
                } else {
                    right = cows[j];
                    up = cows[i];
                }
                if (up.x >= right.x && right.y >= up.y) {
                    times.add(up.x-right.x);
                    times.add(right.y-up.y);
                }
                // else they won't ever intersect, nor will their paths
            }
        }
        // for (int time : times) pw.println(time);

        int lastTime = 0;
        distances = new int[n];
        for (int i = 0; i <= n-1; i++) distances[i] = 1;
        ruts = new TreeSet<Rut>();
        addRuts();
        for (int time : times) {
            int dist = time - lastTime;
            lastTime = time;
            for (int i = active.size()-1; i >= 0; i--) {
                Cow c = active.get(i);
                c.move(dist);
                if (ruts.contains(new Rut(c.x, c.y))) {
                    distances[c.id] += dist-1;
                    c.move(-1);
                    ruts.add(new Rut(c.x, c.y));
                    active.remove(i);
                } else {
                    distances[c.id] += dist;
                }
            }
            addRuts();
        }
        
        if (!active.isEmpty()) {
            for (Cow c : active) {
                distances[c.id] = Integer.MAX_VALUE;
            }
        }
        for (int i = 0; i <= n-1; i++) pw.println(distances[i]==Integer.MAX_VALUE?"Infinity":distances[i]);

        sc.close(); pw.close();

        // we can first look at all pairs of cows and see when their paths will intersect,
        // as those are the only times that anything interesting happens. (in fact, ruts don't
        // even need to be marked as occurring at places which cows occupy at times other
        // than these.) after putting all of these times into a sorted list, we can skip
        // from time value to time value and update each cow accordingly. if, at a specific
        // time point, a cow ends up at a spot where there is a rut, then it instead only
        // travels to the spot right behind it (left if an east cow, bottom if a north cow)
        // and stops there. all of the distances for each cow are marked in an array, and
        // cows are associated with their ids to easily update their distances. in addition,
        // after moving that stopped cow to the spot right before, they are removed from the
        // set of active cows (cows that are still moving) and the spot that they stopped
        // is added to the list of ruts. now, if a cow ends up at a spot that is not a rut,
        // then it is moved to that spot and its distance is updated by how much it moved
        // between those time points. only after doing this for all cows at the current time
        // point do all of the cows have their current positions added as ruts. (the reason
        // why ruts for all of the active cows are not added while looping through them
        // is because if two cows are at the same spot at a time point, we don't want the
        // one we look at first to lay a rut for the other one. the ruts are only immediately
        // added while going through the active cows at the current time point if that cow
        // should be stopped at the time point right before the current time point.) after
        // going through all of the important time points, if there are any cows still
        // actively moving, then they will move for an infinite amount of time.
    }

    static void addRuts() {
        for (Cow c : active) {
            ruts.add(new Rut(c.x, c.y));
        }
    }

    static class Cow {
        int id, x, y;
        char direction;

        public Cow(int id, int x, int y, char dir) {
            this.id = id;
            this.x = x;
            this.y = y;
            direction = dir;
        }

        public void move(int dist) {
            if (direction == 'E') {
                this.x += dist;
            } else {
                this.y += dist;
            }
        }
    }

    static class Rut implements Comparable<Rut> {
        int x, y;

        public Rut(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int compareTo(Rut other) {
            if (this.x != other.x) return Integer.compare(this.x, other.x);
            else return Integer.compare(this.y, other.y);
        }

        // public String toString() {
        //     return "(x="+x+",y="+y+")";
        // }
    }
}