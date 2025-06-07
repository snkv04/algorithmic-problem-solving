import java.util.*;
import java.io.*;

public class FieldReduction {
    static HashSet<Cow> cows = new HashSet<Cow>();
    static TreeSet<Cow> sortedByX = new TreeSet<Cow>(new SortX());
    static TreeSet<Cow> sortedByY = new TreeSet<Cow>(new SortY());
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("reduce.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("reduce.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i <= n-1; i++) {
            String[] split = br.readLine().split(" ");
            cows.add(new Cow(Integer.parseInt(split[0]), Integer.parseInt(split[1])));
        }

        // make two arrays, sorting them by x and y
        // getting the maximum differences, make a large rectangle and get the area
        // any cow within the middle of the rectangle doesn't matter if removed; need to find an edge cow
        // find the maxAreaRemoved between removing the min x cow, max x cow, min y cow, and max y cow
        // remove the corresponding cow and find the area of the new rectangle
        // TreeSet<Cow> sortedByX = new TreeSet<Cow>(new SortX());
        // for (Cow cow: cows) { sortedByX.add(cow); }
        sortedByX.addAll(cows);
        // TreeSet<Cow> sortedByY = new TreeSet<Cow>(new SortY());
        // for (Cow cow: cows) { sortedByY.add(cow); }
        sortedByY.addAll(cows);
        // pw.println(cows+"\n");
        // pw.println(sortedByX+"\n");
        // pw.println(sortedByY+"\n");
        // pw.println("min x = "+sortedByX.first());
        // pw.println("max x = "+sortedByX.last());
        // pw.println("min y = "+sortedByY.first());
        // pw.println("max y = "+sortedByY.last());

        TreeSet<Long> areas = new TreeSet<Long>();
        areas.add((long)((sortedByX.last().x - sortedByX.first().x) * (sortedByY.last().y - sortedByY.first().y)));
        areas.add(getAreaWhenRemoved(sortedByX.first()));
        areas.add(getAreaWhenRemoved(sortedByX.last()));
        areas.add(getAreaWhenRemoved(sortedByY.first()));
        areas.add(getAreaWhenRemoved(sortedByY.last()));
        pw.println(areas.first());

        br.close(); pw.close();
    }

    static class Cow {
        int x;
        int y;
    
        public Cow (int x, int y) {
            this.x = x;
            this.y = y;
        }
    
        public boolean equals (Cow cow) {
            if (this.x == cow.x && this.y == cow.y) return true;
            return false;
        }

        public String toString() {
            return "("+this.x+", "+this.y+")";
        }
    }
    
    static class SortX implements Comparator<Cow> {
        public int compare (Cow cow1, Cow cow2) {
            if (cow1.x != cow2.x) return Integer.compare(cow1.x, cow2.x);
            else return Integer.compare(cow1.y, cow2.y);
            // if it only compared the x, then cows would be considered to be equal if their
            // x-values were the same
        }
    }
    
    static class SortY implements Comparator<Cow> {
        public int compare (Cow cow1, Cow cow2) {
            if (cow1.y != cow2.y) return Integer.compare(cow1.y, cow2.y);
            else return Integer.compare(cow1.x, cow2.x);
        }
    }

    static long getAreaWhenRemoved (Cow cow) {
        sortedByX.remove(cow);
        sortedByY.remove(cow);
        long area = (sortedByX.last().x - sortedByX.first().x) * (sortedByY.last().y - sortedByY.first().y);
        sortedByX.add(cow);
        sortedByY.add(cow);
        return area;
    }
}