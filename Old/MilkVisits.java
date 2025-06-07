import java.util.*;
import java.io.*;

public class MilkVisits {
    static ArrayList<Integer>[] adj;
    static TreeSet<Integer> unlabeled;
    static Stack<Integer> s;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("milkvisits.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("milkvisits.out")));

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        char[] farmsGH = br.readLine().toCharArray();

        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Integer>();
        }
        for (int i = 1; i <= n-1; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        //// the basic solution would be to check the path from each farmer's start to their end,
        // but finding the path before even checking it would take too long if the tree is large
        //// so, instead, we break up the graph into "connected components" where each component
        // has all of its nodes connected by being the same milk type
        //// this creates fully disjoint components
        //// now, to check if there is a farm of the farmer's preference on the singular path
        // between their start and end, we can check if the start and end are in different components;
        // if they are, then it is guaranteed that the preferred type will be on the path,
        // as since we know that the components are separated by type, crossing through two will
        // make sure that the path has both
        //// if the encompassing component of the start and end are the same, we can just check
        // if the type of that component is the one that the farmer prefers
        //// to generate and record the "components", we can have a treeset of the unclosed farms
        // so far as well as an array of each farm's label, and a farm getting added to a component
        // involves that farm being removed from the treeset and getting its value in the array;
        // we use a dfs to cover the entire component, and when we finish the component, then the
        // farms in the new component are given a new label
        //// note: by the way, instead of using a treeset to see which farms are unlabeled so far,
        // i can just go through all the farms one by one; i originally did not want to do this,
        // as i thought that this would mean that i would have to check every single farm for if it
        // has a label and if it doesn't, then do a dfs that could have n computations, meaning that
        // the overall complexity would be O(n^2); however, the sum of the operations involved in all
        // the DFSs across all the farms is n, and there are n checks to see if each farm has yet been
        // visited or not, so the complexity is actually O(2n)=O(n); so, what could then be done is
        // that each farm could be checked if it has been labeled or not, and if not, then a dfs
        // could be run from that farm to label every farm in the connected component
        
        //// what was learned from this?
        // (understand that i could always be wrong about this conclusion)
        // instead of finding the path from one node to another in a graph (or tree) and then
        // evaluating that path, as finding a path can be n expensive and we may have to do that
        // m times, there could be a way of grouping up the nodes into connected components
        // (defined in a specific way given the context) and then analyzing which groups the
        // beginning and end nodes of a path are in
        int[] componentLabels = new int[n];
        unlabeled = new TreeSet<Integer>();
        for (int i = 0; i <= n-1; i++) { unlabeled.add(i); }
        int component = 1;
        while (!unlabeled.isEmpty()) {
            int firstElement = unlabeled.first();
            if (componentLabels[firstElement] == 0) {
                // do dfs here
                s = new Stack<Integer>();
                s.add(firstElement);
                while (!s.isEmpty()) {
                    int popped = s.pop();
                    if (componentLabels[popped] == 0) {
                        componentLabels[popped] = component;
                        unlabeled.remove(popped);
                        for (int adjacentFarm : adj[popped]) {
                            if (componentLabels[adjacentFarm] == 0 && farmsGH[adjacentFarm] == farmsGH[popped])
                                s.add(adjacentFarm);
                        }
                    }
                }
                component++;
            } else {
                unlabeled.remove(firstElement);
            }
        }

        for (int i = 0; i <= m-1; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            char preference = line[2].charAt(0);
            if (componentLabels[a] == componentLabels[b]) {
                pw.print((farmsGH[a] == preference) ? "1" : "0");
            } else {
                pw.print("1");
            }
        }

        br.close(); pw.close();
    }
}
