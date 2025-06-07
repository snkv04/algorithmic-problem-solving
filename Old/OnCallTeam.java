import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class OnCallTeam {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        /*
         * basically, the problem is asking for the maximum subset size of the set of services such that
         * ANY subset of that size allows for a perfect matching between that subset of services and the
         * people, where the edges are constructed between tasks and the people that can solve them. so,
         * the idea for the solution is to use Hall's Marriage Theorem to check what subset size does not
         * satisfy the theorem's condition. since a perfect bipartite matching between some set of tasks
         * and the set of all people is possible if every subset of that (sub)set of tasks has its neighborhood
         * as at least the size of the subset, we can go through every subset of the original list of tasks,
         * checking if the neighborhood condition is met. if not, then ANY superset of that set will not
         * have a good matching for that superset, so a value of k that is greater than or equal to the size
         * of that set will not work because it may be possible that this bad set is included in those k
         * cards. so, we can just find the minimum subset size that does not meet the neighborhood
         * condition, and all subset sizes below that would be fine.
         * the issue is, that the number of subsets is 2^20 = 1048576, and each time, the checking of the
         * neighborhood takes 20 * 3 * 10^4, because we have to check all people for all tasks, and it
         * could be possible that every task lets every person deal with it. how can this be optimized?
         * the key here is to recognize that the condition we care about is that the neighborhood size
         * is at least the size of the subset we're currently looking at. once we exceed that, we don't
         * need to check anymore neighbors. what is the new time complexity if we do this? suppose we're
         * checking a subset of 18 vertices, and there are 3*10^4 people who are all able to fix the same
         * 17 tasks. at that point, since we are iterating through the <=20 tasks and NOT through the
         * <=3*10^4 people in the outer loop (or i guess the medium loop, since the outermost loop is
         * going through each subset of tasks), once we get to the 18th person, then we're done for that
         * task. so, this means that for each subset we look at, each task can have at most (subset size)
         * people that we care about, so there are m^2 people to look through. in the end, this gives us
         * an m^2 * 2^m algorithm, which passes under the time limit. an additional optimization that needs
         * to be added though (because without it, it's so close to the time limit that sometimes it
         * passes and sometimes it doesn't) is that if we are looking at a subset with a size greater
         * than or equal to a value we already previously deemed to be unable to get any sets etc etc,
         * then it doesn't need to be checked.
         * 
         * how could i arrive at this solution myself?
         * first off, the limit of tasks is 20, so i could think about iterating through all the subsets
         * of tasks, either as an inner loop or some outer loop or something. maybe it would be possible
         * to iterate over every subset, and for each we can see if there is a matching that includes all
         * of the tasks in the subset so then we can get the maximum k where all the subsets of at most
         * that size have a good matching? well, that would be too slow, since we have to make the graph
         * and find the matching for every subset. now, since this has to deal with perfect matchings
         * where one part of the bipartite graph varies in size and its vertices, maybe it could involve
         * hall's theorem somehow. actually, we could look at the hall's theorem condition from a different
         * angle (not the converse), meaning that since it tells us something about a subset of vertices
         * if all of ITS subsets meet some condition, we could go through all subsets and determine some
         * properties about all of their supersets if it meets (or rather, doesn't meet) the condition.
         * specifically, if a subset doesn't meet the neighbor condition, then all sets of tasks containing
         * it will not have a perfect matching from them to the people handling the tasks, so going back
         * to the problem, all of those k values greater than or equal to the size of the subset will not
         * work because the sets containing that subset will not be able to be properly handled. so, this
         * works. however, wouldn't it be too slow? well, first make sure to see it through to the end
         * and TRY OUT THE BRUTE FORCE STRATEGY before trying to prematurely optimize it, because maybe
         * it will work or maybe although it won't it could still have some optimization that would make
         * it pass. so, in this case, just check for the condition we care about, and also check for the
         * cases that we don't even need to consider because we already previously ruled out such k values.
         * then, with those optimizations, it passes.
         */
        
        String[] s = br.readLine().split(" ");
        int n = Integer.parseInt(s[0]), m = Integer.parseInt(s[1]);
        int[] countPerTask = new int[m];
        int[][] handlers = new int[m][n];
        for (int i = 0; i < n; i++) {
            String str = br.readLine();
            for (int j = 0; j < m; j++) {
                if (str.charAt(j)=='1') handlers[j][countPerTask[j]++] = i;
            }
        }

        int minBad = m+1;
        for (int mask = 1; mask < (1 << m); mask++) {
            HashSet<Integer> neighbors = new HashSet<>();
            int subsetSize = 0;
            for (int j = 0; j < m ; j++) {
                if (((mask >> j) & 1) == 0) continue;
                subsetSize++;
            }
            if (subsetSize >= minBad) continue;

            for (int j = 0; j < m && neighbors.size() < subsetSize; j++) {
                if (((mask >> j) & 1) == 0) continue;
                for (int i = 0; i < countPerTask[j]; i++) {
                    neighbors.add(handlers[j][i]);
                    if (neighbors.size() == subsetSize) break;
                }
            }

            if (neighbors.size() < subsetSize) {
                minBad = Math.min(minBad, subsetSize);
            }
        }
        pw.println(minBad - 1);
    }
}
