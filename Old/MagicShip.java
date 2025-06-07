import java.util.*;
import java.io.*;

public class MagicShip {
    static Position[] windPrefix;
    static int x1, y1, x2, y2, n;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        x1 = Integer.parseInt(line[0]);
        y1 = Integer.parseInt(line[1]);
        line = br.readLine().split(" ");
        x2 = Integer.parseInt(line[0]);
        y2 = Integer.parseInt(line[1]);
        n = Integer.parseInt(br.readLine());

        char[] wind = br.readLine().toCharArray();
        windPrefix = new Position[n+1];
        windPrefix[0] = new Position(0, 0);
        for (int i = 1; i <= n; i++) {
            windPrefix[i] = windPrefix[i-1].move(wind[i-1]);
        }

        long low = 1, high = Long.MAX_VALUE / 2, ans = -1;
        while (low <= high) {
            long mid = (low + high) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        pw.println(ans);

        br.close(); pw.close();

        // we want to see how many moves we need to get to the point (x2,y2) from (x1,y1)
        // taking into consideration the wind on each move. for any given number of moves x,
        // what we can instead do is see where the wind takes us after x days, then if
        // we can reach the endpoint with x windless moves after that, then that value of x
        // works. we can see that if any arbitrary x returns true, then all values greater
        // than x will also work because after reaching the endpoint in x days, all
        // further days can simply be spent counteracting the wind and staying in the
        // same place. so, this is a monotonic function and can be binary searched. for each
        // value being checked, we can do the above: finding location after x days of wind,
        // then seeing if moves to destination is less than or equal to x.
        // if x is less than or equal to n, then to see where we end up after x days, we
        // have to go through all of the wind array up to x and change our current position
        // each time. to do this query for each binary search value will take way too long.
        // so, we can use what is essentially a prefix sum for position, where an index
        // tells us where we end up after that index many days (whether we start from 0,0
        // or x1,y1 doesn't matter because we can just shift to start from x1,y1 anyway).
        // now, to deal with how x may be vastly larger than n, notice that after 2n days,
        // the distance from 0,0 is double the distance from 0,0 after n days, triple with
        // 3n, etc. so, for large values of n, we can take prefix(n) and multiply that
        // coordinate point by floor(x / n), and then add that coordinate to prefix(x mod n).
        // (also, make sure to account for any weirdness with array indices.) now, whether
        // there's wind or not, there is no reason for moving the ship in a direction other
        // than toward the destination, other than canceling out the wind once the ship is
        // there (which won't happen anyway once binary search reaches the min number x of
        // moves, as required moves should equal x). so, at this point in the check function
        // we can just check the Manhattan/taxi distance between where the wind sends the
        // ship after x days and the destination (since this is, as mentioned, the minimum
        // number of moves), and if it's leq x then return true, otherwise return false.
    }

    static class Position {
        long x, y;

        public Position(long x, long y) {
            this.x = x;
            this.y = y;
        }

        public Position move(char direction) {
            long newx = x, newy = y;
            if (direction == 'L') newx--;
            if (direction == 'R') newx++;
            if (direction == 'U') newy++;
            if (direction == 'D') newy--;
            return new Position(newx, newy);
        }

        public Position multiply(long k) {
            long newx = x * k;
            long newy = y * k;
            return new Position(newx, newy);
        }

        public Position add(Position p) {
            long newx = x + p.x;
            long newy = y + p.y;
            x += p.x;
            y += p.y;
            return new Position(newx, newy);
        }

        public String toString() {
            return "(x="+x+",y="+y+")";
        }
    }

    static boolean check(long moves) {
        // System.out.println("checking ="+moves);
        long fullWindCycles = (long) moves / n;
        // System.out.println("full wind cycles="+fullWindCycles);
        Position placeAfterWind = windPrefix[n].multiply(fullWindCycles);
        // if (moves%n != 0)
        placeAfterWind = placeAfterWind.add( windPrefix[(int) (moves%n)] ); // mod n not len(prefix) so no issues
        // System.out.println("placeafterwind = "+placeAfterWind);
        placeAfterWind = placeAfterWind.add(new Position(x1, y1));
        // System.out.println("including x1, y1 = "+placeAfterWind);
        // System.out.println();

        // math !!!

        if (Math.abs(x2 - placeAfterWind.x) + Math.abs(y2 - placeAfterWind.y) <= moves) {
            // System.out.println("check of "+moves+" is true");
            return true;
        }
        // System.out.println("check of "+moves+" is false");
        return false;
    }
}
