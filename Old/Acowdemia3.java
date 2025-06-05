import java.util.*;
import java.io.*;

public class Acowdemia3 {
    static int n, m;
    static char[][] pasture;
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        pasture = new char[n][0];
        for (int i = 0; i <= n-1; i++) {
            pasture[i] = br.readLine().toCharArray();
        }

        int ans = 0;
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= m-1; j++) {
                if (pasture[i][j]=='G') {
                    if (isCow(i+1, j) && isCow(i-1, j)) {
                        ans ++;
                        pasture[i][j] = '.';
                    } else if (isCow(i, j+1) && isCow(i, j-1)) {
                        ans++;
                        pasture[i][j] = '.';
                    }
                }
            }
        }
        // pw.println(ans);
        // for (char[] gridline : pasture) pw.println(gridline);

        TreeSet<Pair> friendships = new TreeSet<Pair>();
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= m-1; j++) {
                if (pasture[i][j] == 'G') {
                    // int numAdjacent = 0;
                    if (isCow(i, j-1) && isCow(i-1, j)) {
                        // numAdjacent+=2;
                        friendships.add(new Pair(new Cow(i-1, j), new Cow(i, j-1)));
                    }
                    if (isCow(i-1, j) && isCow(i, j+1)) {
                        // numAdjacent+=2;
                        friendships.add(new Pair(new Cow(i-1, j), new Cow(i, j+1)));
                    }
                    if (isCow(i+1, j) && isCow(i, j-1)) {
                        // numAdjacent+=2;
                        friendships.add(new Pair(new Cow(i, j-1), new Cow(i+1, j)));
                    }
                    if (isCow(i+1, j) && isCow(i, j+1)) {
                        // numAdjacent+=2;
                        friendships.add(new Pair(new Cow(i, j+1), new Cow(i+1, j)));
                    }
                    // if (numAdjacent > 0)
                    // pw.println("i="+i+", j="+j+", and numAdjacent to this grass is = "+numAdjacent);
                }
            }
        }
        ans += friendships.size();
        // pw.println(friendships);
        pw.println(ans);

        br.close(); pw.close();

        // at first, i was thinking that since every piece of grass can only be used once,
        // for each piece of grass, i’ll look left, right, down, and up for the nearest cows
        // in each direction, and for the direction with two cows and the least number of grasses
        // (keeping track of those for both directions), i’ll use that grass on the nearest cow
        // in that direction. then i realized that edge cases would make this algorithm fail,
        // but i also realized that i read the problem wrong and that each grass can only use
        // directly adjacent cows.
        // then, i considered that for each cow, we can look the cows it can be friends
        // with, and prioritize the pairs that have the least number of grasses connecting
        // them, making as many as possible. since every pair of cows can only have at most
        // 2 grasses connecting them, though, there are edge cases that also invalidate this
        // solution.
        // the next solution is to look at each grass, and see how many cows it can connect.
        // if there are two adjacent cows, then those cows are the only ones that the grass
        // can be used for, so it is used for those. however, multiple (2) pieces of grass
        // can be used to connect the same two cows, so we need to keep track of which pairs
        // have been created already in order to avoid the same friendship being recorded
        // multiple times. if a grass has more than 2 cows adjacent to it, then there are
        // either 3=3C2 pairs that can use that grass or 6=4C2 pairs. either way, for any of
        // the cows adjacent to the current grass, no matter how many other cows or which cows
        // it can be paired with, it is guaranteed that this grass can be used once (i.e. will
        // not be in a situation such that all of the adjacent cows are already paired with
        // each other) because there will be at least one pair of cows that stretch in a straight
        // line over the grass that cannot be connected in any way other than with the current
        // grass. so, for each grass that only has exactly two adjacent cows, add the pair it
        // connects to a set (not multiset), and the answer is the number of grasses that have
        // 3 or 4 adjacent cows plus the size of the set of pairs which were formed from grasses
        // with only two adjacent cows.
        // the key observation here was that a grass with two cows across the grass (as opposed
        // to cows being perpendicularly connected with that grass) will be the only grass that
        // can pair up those two cows, and so using this grass for that purpose would always be
        // optimal (regardless of if or not there are other, perpendicular cows) whether using
        // it for cows above and below or to the left and right. for example, if there’s a cow
        // above, left, and right, then using it for left and right is better than the other two
        // combinations, because there’s a chance that left/up and up/right have their own grass,
        // and even if they don’t, then the grass can only be used once so in that case it doesn’t
        // matter which cows it brings together. having this observation allows me to greedily deal
        // with at least some grasses, and then to deal with the remaining grasses that have at
        // most two grasses, they are all hosts of perpendicular cows at most and this is its own
        // problem but it can be solved using the strictly distinct sets method (which i have used
        // before in other problems).
        // another solution, which is slightly longer, slightly more intuitive, and very similar,
        // is to first look at all grasses that have at least one pair of cows on a straight line
        // across the grass, and for each of them, increment the answer (since no other grass can
        // make those two cows connected) and turn it into a dot. this makes use of the already
        // discussed observation that it will always be optimal to use this grass for the purpose
        // of connecting two such cows. this also makes use of READING THE PROBLEM CAREFULLY, since
        // being able to use each grass only once but each cow multiple times enables this solution
        // to work. after going through all of these grasses, we can deal with the grasses with at
        // most two adjacent cows (which is any grass left with any cows adjacent, since if not then
        // it has been taken care of by turning it into a dot), which all have two perpendicular cows,
        // by adding the pair of cows it is adjacent to into a set of these pairs. if a pair
        // appears multiple times (which would happen if two grasses connect the same two cows),
        // then it is reduced into being counted only once (just like in the other solution). and
        // since each grass only has two cows adjacent to it now, there are no choices of pairs of
        // cows to pick from. then we can just add the number of grasses used from the first step
        // to the number of cow pairs from the second step, and that is the answer. this differs
        // from the first solution in that for grasses with exactly two cows adjacent to it in the
        // beginning, in the first solution it would get added to the pairs set regardless of if
        // those two were in a straight line or perpendicular from the grass, while in the second
        // solution a grass with two parallel cows would be counted immediately and a grass with
        // two perpendicular cows would get added to the set after the first step. it’s mainly a
        // difference in the intuition used to solve the problem. it’s basically separating the two
        // steps of the first solution into two passes over all the pieces of grass, instead of
        // passing over all of the grass at once.
    }

    static boolean isCow(int i, int j) {
        return i >= 0 && i <= n-1 && j >= 0 && j <= m-1 && pasture[i][j]=='C';
    }

    static class Cow implements Comparable<Cow> {
        int i, j;

        public Cow (int i, int j) {
            this.i = i;
            this.j = j;
        }

        public int compareTo(Cow other) {
            if (this.i != other.i) return Integer.compare(this.i, other.i);
            else return Integer.compare(this.j, other.j);
        }

        public String toString() {
            return "("+i+", "+j+")";
        }
    }

    static class Pair implements Comparable<Pair> {
        Cow c1, c2;

        public Pair(Cow c1, Cow c2) {
            this.c1 = c1;
            this.c2 = c2;
        }

        // it's already guaranteed that in a pair, the first cow is "less" than
        // the second one (sorted by i then by j)
        // this is important to ensure that duplicate pairs (which are pairs with
        // the same cows) always have the cows appear in the same order to make
        // comparing the two pairs much easier
        public int compareTo(Pair other) {
            if (this.c1.compareTo(other.c1)!=0) return this.c1.compareTo(other.c1);
            else return this.c2.compareTo(other.c2);
        }
        
        public String toString() {
            return "<"+c1.toString()+" and "+c2.toString()+">";
        }

        // public boolean equals(Object other) {
        //     Pair otherPair = (Pair) other;
        //     return this.compareTo(otherPair)==0;
        // }
    }
}
