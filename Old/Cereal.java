import java.util.*;
import java.io.*;

public class Cereal {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("cereal.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cereal.out", false)));

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        Cow[] cows = new Cow[n+1];
        for (int i = 1; i <= n; i++) {
            line = br.readLine().split(" ");
            cows[i] = new Cow(Integer.parseInt(line[0]), Integer.parseInt(line[1]));
        }

        // TreeSet<Integer> eaten = new TreeSet<>();
        int[] numCows = new int[n+1];
        int[] takenBy = new int[m+1];
        for (int i = n; i>=1; i--) {
            int cow = i;
            int cereal = cows[cow].first;
            while (true) {
                if (takenBy[cereal] == 0) {
                    takenBy[cereal] = cow;
                    if (i==n) numCows[i]=1;
                    else numCows[i]=numCows[i+1]+1;
                    break;
                } else {
                    // the current cow's cereal was taken
                    if (takenBy[cereal] > cow) {
                        // it was taken by a cow later in line
                        int other = takenBy[cereal];
                        takenBy[cereal] = cow;
                        // now checking if the other cow had this cereal as its
                        // first or second choice
                        if (cereal == cows[other].first) {
                            // the other cow had this cereal as its first choice, so now
                            // we treat this other cow as the head of the chain and recurse
                            cow = other;
                            cereal = cows[other].second;
                        } else {
                            // this means (cereal==cows[other].second), i.e. the other
                            // cow had no other choice
                            numCows[i]=numCows[i+1];
                            break;
                        }
                    } else {
                        // it was taken by a cow earlier in line, which means
                        // that the cow earlier in line has chosen its second choice.
                        // therefore, this cow gets no food, since its first and second
                        // choice are taken by cows earlier than it in line.
                        numCows[i] = numCows[i+1];
                        break;
                    }
                }
            }
            
            // if (eaten.contains(cows[i].first)) {
            //     int cowThatTook = takenBy[cows[i].first];
            //     if (!eaten.contains(cows[cowThatTook].second)) {
            //         eaten.add(cows[cowThatTook].second);
            //         takenBy[cows[cowThatTook].second] = cowThatTook;
            //         numCows[i]=numCows[i+1]+1;
            //     } else {
            //         // cowThatTook is either settling for its second option, making the number
            //         // of cows not increase, or not being able to take it because another one
            //         // in front of it took it, also not making the answer increase.
            //         int cowThatTook2 = takenBy[cows[cowThatTook].second];
            //         if (cowThatTook2 < cowThatTook) {
            //             numCows[i]=numCows[i+1];
            //         } else {
                        
            //             if (eaten.contains(cows[cowThatTook2].second)) {
            //                 numCows[i]=numCows[i+1];
            //             } else {
            //                 takenBy[cows[cowThatTook2].second] = cowThatTook2;
            //                 eaten.add(cows[cowThatTook2].second);
            //                 numCows[i]=numCows[i+1]+1;
            //             }
            //             takenBy[cows[cowThatTook].second] = cowThatTook;
            //         }
            //     }
            //     takenBy[cows[i].first] = i;
            // } else {
            //     eaten.add(cows[i].first);
            //     if (i==n)numCows[i]=1;
            //     else numCows[i] = numCows[i+1]+1;
            //     takenBy[cows[i].first] = i;
            // }
        }
        for (int i = 1; i <= n; i++) pw.println(numCows[i]);

        br.close(); pw.close();

        // i had a very similar general idea but i messed up the implementation
        // by not making the whole thing about changing previous cows into a recursive
        // program. basically, moving in reverse, we know that if a type of cereal is
        // eaten by a cow in the back, then no matter how many cows are removed or added
        // to the line in front of that cow, that cereal will still be eaten but only the
        // specific cow who is eating it will change. keep track of which cow is eating
        // which cereal for this reason. now, a cow in front will always get their first
        // choice, since we are filling in from the back, and will only opt for second choice
        // in the situation that a cow even in front of it also chooses its first choice.
        // so we can assume for each cow we fill in, that cow gets its first choice.
        // if that first choice is taken, look at who took it. for the first cow in the
        // future chain of recursion, we know that the one who took it is behind the current
        // cow. if the other cow originally had the cereal in question as its second choice,
        // then we know that cow now gets no food from now on, and because in adding the
        // new cow an old one gets kicked out, the answer for when this many cows are
        // in line is the same as if the front one was removed (although the cows eating
        // the different cereals are different). however, if the other cow had the cereal
        // as its first choice, then we set that cow as the current cow and its first choice
        // cereal as the current cereal. we once again check if that cereal is taken, etc.
        // remember, if it isn't then we're good. if it is by a later cow, then we recurse
        // using that cow. however, if it is taken by a cow to the left in line, then
        // that means this other2 cow avoided the recursion step in the algorithm
        // i just mentioned, meaning that this other2 cow has its cereal as the second
        // choice of the original other cow. this means that the original othercow
    }

    static class Cow {
        int first, second;

        public Cow(int first, int second) {
            this.first=first;
            this.second=second;
        }
    }
}
