import java.util.*;
import java.io.*;

public class CircularBarnSilver {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("cbarn.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));

        int n = Integer.parseInt(br.readLine());
        int[] c = new int[n];
        for (int i = 0; i <= n-1; i++) {
            c[i] = Integer.parseInt(br.readLine());
        }

        int max = c[n-1];
        int maxIndex = n-1;
        int curr = c[n-1];
        for (int i = n-2; i >= 0; i--) {
            curr--;
            curr += c[i];
            if (curr > max) {
                max = curr;
                maxIndex = i;
            }
        }
        
        long energy = 0;
        int currCows = 0;
        for (int i = 0; i <= n-1; i++) {
            int currIndex = (maxIndex+i)%n;
            currCows += c[currIndex];
            currCows--;
            energy += currCows * currCows;
        }
        pw.println(energy);

        br.close(); pw.close();

        // first off, instead of calculating the walk around the barn for each cow,
        // we can pass through the entire circle, picking up and dropping off cows at
        // certain rooms and using math to determine the sum of the squares of the
        // distances for each cow. now, we can't just start at any point around the
        // circle, since if we encounter one or multiple rooms when we don't have any
        // previously picked up cows to drop off, then that means we should have
        // started more counterclockwise than where we tried starting off. so, we
        // start with one counterclockwise pass at a random location (at index n-1
        // out of convenience), where we iterate through each room counterclockwise,
        // dropping off one cow and adding in the amount of cows that start off
        // sitting in that room. we find the room at which we hold the maximum cows
        // and record its index. (it's ok if, during the loop, the cows currently being
        // held go into the negatives, as getting the max value will still apply
        // regardless.) it is guaranteed that this is either the single best or one
        // of the equally best places to start, because since it is guaranteed that
        // there are n total cows across the n rooms regardless of the distribution,
        // when we actually do our clockwise pass, we know for sure that we will never
        // encounter an empty room (0 cows contained) without holding at least one
        // cow to drop it off.
        // now, for the actual clockwise pass, we want to drop off cows as soon as
        // possible. for example, if we have two rooms where the number of cows are
        // 2 then 1, it is much better to move 1 from the first to the second then 1
        // from the second to the third than to move 1 cow from the first room to the
        // third room just because there's already one in the second room. the first
        // option uses 1^2+1^2=2 energy while the second uses 2^2=4 energy. in general,
        // holding cows for any longer than they need to is harshly punished by the
        // d^2 energy being calculated instead of just d, the latter of which would
        // mean it doesn't matter. so, using this method of picking up and dropping
        // off cows to make the circular pass, now we just have to figure out how
        // to calculate the sum of each cow's distance squared efficiently. we can
        // simulate the circular pass by dropping off one cow at every single room
        // (reasoning explaiend above) and picking up all of the cows from that room.
        // a key observation is that the number of cows currently being held as we
        // leave each room is equal to the distance that a cow starting at that room
        // will travel. (consider the case where 3 cows are picked up from one room
        // and the following 3 rooms each have 0 cows. the first cow will be dropped
        // off in one room, the second has to wait for two rooms, etc. the number of
        // cows after leaving the rooms in order are 3, 2, 1, 0, mirroring the values
        // we want. this was observed by working through the example given.) with this,
        // we can calculate the final energy using this value (cows waiting to be dropped
        // off) from each room.
    }
}
