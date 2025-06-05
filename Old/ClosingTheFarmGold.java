import java.util.*;
import java.io.*;

public class ClosingTheFarmGold {
    static ArrayList<Integer>[] adj;
    static int[] parent;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("closing.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("closing.out")));

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Integer>();
        }
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        //// summary
        // first build the adjacency list
        // then, go and add farms instead of removing farms (going in reverse from what is given)
        // also have a parent node list for DSU, and initialize all the parents to themselves
        // have a count for the number of components currently
        // for each farm that is added, increase the number of components
        // then, within the for loop, go through the adjacency list, and if the adjacent node
        // is opened and not within the same component (using DSU root find), then union the
        // two components and decrement the component number
        // at the end of that main for loop iteration, if the number of components is equal to
        // 1, then the answer is YES, otherwise it is NO
        // at the end, print these results in reverse order

        //// justification
        // we are going in reverse order because DSU doesn't support removing edges but rather
        // adding edges.
        // the reason why we don't connect each new barn being added to ALL of its
        // adjacent barns but only to the ones that are already opened is: there could be
        // unopened barns at a certain step (where step means that we are adding a specific barn)
        // that are connected to from a currently added barn, and then that unopened one could
        // join together a previously added barn and a currently added barn that aren't otherwise
        // connected, resulting in the algorithm saying that the barn is fully connected at this
        // time when it actually isn't.
        // a single barn being added can connect several connected components by being the
        // connector piece that combines them into one. so to take that into consideration,
        // we could check to see if each new barn is connected to each and every one of the previous
        // barns, but it would be much more efficient to just have a count of the components. and so
        // when a new barn is added, it will always be considered a new component, then through the
        // edges across which it connects to already opened barns, the number of components goes down
        // for each component it connects to that it is not already a part of. also, remember that
        // the DSU or parents array is just a tool for seeing in which connected component each node
        // is. don't forget that.
        // it already makes sense that we don't reduce the components count if the new barn's adjacent
        // edge is to another barn in the same component as it. but how would this happen? it would
        // happen if one edge connects to a barn and then another edge connects to a barn that was
        // in the same component as that first adjacent barn. fairly simple.
        
        //// what was learned from this?
        //// (understand that i could always be wrong about this conclusion)
        // instead of going through the queries in the normal order, we can sometimes go through it
        // in a different order, like reversed, if it is more helpful that way, such as to support a
        // data structure (like DSU). also, instead of having a hashset of all the objects/nodes that
        // have a certain feature, you can just have a boolean array of all the objects/nodes which
        // says whether or not a given node has the feature.
        // additionally, it can be very helpful to have a variable to count a big picture, overarching
        // part of the problem (like the number of components in this case), and also think of manipulating
        // variables in interesting and creative ways instead of only using them for incrementing.
        // lastly, please just try to always draw or write something for the problem instead of
        // just trying to do everything in your head, as laying everything out in front of you can
        // help get less confused. having a drawing/diagram that is a decent representation
        // of an example of the problem can let you play around with the different aspects
        // of the problem, letting you understand it better.
        int[] queries = new int[n];
        parent = new int[n];
        for (int i = n-1; i >= 0; i--) {
            int openedFarm = Integer.parseInt(br.readLine()) - 1;
            queries[i] = openedFarm;
            parent[i] = i;
        }

        String[] resultsReversed = new String[n];
        boolean[] opened = new boolean[n];
        int components = 0;
        for (int i = 0; i <= n-1; i++) {
            int openedFarm = queries[i];
            components++;
            opened[openedFarm] = true;

            for (int adjacentBarn : adj[openedFarm]) {
                if (opened[adjacentBarn] && find(openedFarm) != find(adjacentBarn)) {
                    union(openedFarm, adjacentBarn);
                    components--;
                }
            }

            resultsReversed[i] = (components == 1) ? "YES" : "NO";
        }

        for (int i = n-1; i >= 0; i--) {
            pw.println(resultsReversed[i]);
        }

        br.close(); pw.close();
    }

    static void union(int a, int b) {
        int c = find(a);
        int d = find(b);
        if (c != d) {
            parent[d] = c;
        }
    }

    static int find(int node) {
        if (parent[node] == node) {
            return parent[node];
        } else {
            parent[node] = find(parent[node]);
            return parent[node];
        }
    }
}
