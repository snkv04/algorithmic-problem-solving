import java.util.*;
import java.io.*;

public class MooParticle {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("moop.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("moop.out")));

        int n = Integer.parseInt(br.readLine());
        Particle[] particles = new Particle[n];
        for (int i = 0; i <= n-1; i++) {
            int[] line = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            particles[i] = new Particle(line[0], line[1]);
        }

        // // if the particles are plotted on a graph, then for any particle p, any other particle
        // to the right and up of p, or to the left and down of p, can interact with p
        // // looking at a group of particles that can all interact with each other in like a chain
        // or with more connections, if care is taken in specifically making the ones disappear that
        // are not connected to too many others, it can be guaranteed that every single particle in the
        // group can disappear, leaving only the last one left
        // // let a (undirected, unweighted) graph be drawn between the particles, having an edge
        // representing if two particles can interact or not; then the number of particles remaining
        // if as many of them are removed optimally as possible would just be the number of connected
        // components, because each connected component could be reduced to a single particle
        // // so we are just looking for the number of connected components; however, constructing
        // the graph of which nodes are connected to which nodes will take O(n^2)
        // // on a graph, a connected component is visually represented by a group of particles that
        // are all connected through having particles in common to the right and up or
        // to the left and down, and components are separated when every particle to the right is
        // below the ones to the left
        // // so, we can go through all of the particles from left to right, and if for each
        // particle we have a variable representing the minimum value to the left and maximum
        // value to the right, we just can count how many times it is true that the minimum value
        // to the left is greater than the maximum value to the right, and that is how many
        // connected components we have in the graph
        // // reasoning behind this is: normally, it would feel natural to just look from left to
        // right through the particles and as soon as one of the particles is less than the minimum y
        // so far (i.e. strictly to the right and down from everything so far) then count a new
        // connected component, but the issue with this is that there might be another particle down
        // the line to the right that connects both the newest particle and the whole component from before;
        // so, for each particle we also keep a variable representing the maximum value including
        // that particle to the right, and so if we come across that particle later on a left-to-right
        // pass, then we would notice that it connects us back to our left hand component later on
        // and not create a new connected component; on the other hand, if the max y value to the right
        // is below the minimum y value to the right, then we know the right cannot connect with
        // the left and start a new guaranteed component
        // // to store the min_across_the_left y values, we do a left-to-right pass, and to
        // get the max_across_the_right y values, we do a right-to-left pass, and then to calculate
        // the number of connected components, we can do either but a left-to-right pass is more
        // intuitive
        Arrays.sort(particles, new Comp());
        int[] min_across_left = new int[n];  // referring to y values
        int[] max_across_right = new int[n]; // referring to y values
        min_across_left[0] = particles[0].y;
        for (int i = 1; i <= n-1; i++) {
            min_across_left[i] = Math.min(min_across_left[i-1], particles[i].y);
        }
        max_across_right[n-1] = particles[n-1].y;
        for (int i = n-2; i >= 0; i--) {
            max_across_right[i] = Math.max(max_across_right[i+1], particles[i].y);
        }

        int count = 1;
        for (int i = 1; i <= n-1; i++) {
            if (min_across_left[i-1] > max_across_right[i]) count++;
        }
        pw.println(count);

        br.close(); pw.close();
    }

    static class Particle {
        int x, y;

        public Particle(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public String toString() {
            return "(x="+x+",y="+y+")";
        }
    }

    static class Comp implements Comparator<Particle> {
        public int compare(Particle p1, Particle p2) {
            if (p1.x != p2.x) return Integer.compare(p1.x, p2.x);
            else return Integer.compare(p1.y, p2.y);
        }
    }
}
