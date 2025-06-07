import java.util.*;
import java.io.*;

public class Pareidolia {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;

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
         * The obviously correct but too slow solution in O(n^2) is, for each starting index
         * from 0 to n-1, loop through the characters starting at that index and greedily keep
         * track of the earliest occurrence of each character in bessie, and when the word is
         * finished, then add the number of characters left in the string (including the end
         * character 'e') to the answer, since that word will appear for every string starting
         * at the current start index (which are all prefixes of the suffix which ranges from the end
         * to the given start index) and ending on or after the 'e' letter ending the "bessie"
         * subsequence. If there is another occurrence of bessie, then do the same again,
         * repeatedly.
         * 
         * To speed this up to O(n), at each character in the string t, we can keep track of how
         * many single iterations of the outer loop from above (which includes a full series of
         * iterations of the inner loop, or a single instance of the greedy algorithm being run
         * with each instance having a different starting point in the string) have reached the
         * end of a "bessie" subsequence at that current character, and then multiply that number
         * by the number of characters on and to the right like was done before. The number of
         * characters to the left of the 'b' in "bessie" is already taken care of by counting
         * how many of the greedy algorithms have already started by that point. To keep it
         * accurate and ensure that this algorithm works in every case, including when "bessie"s
         * overlap, we should also keep track of, for each character in the string t, how many
         * greedy algorithms are currently at each point in the string "bessie" (distinguishing
         * between different occurrences of the same letter), so that the number at the second
         * 's' at a point in the overall string, for example, would be equal to the number of
         * greedy algorithms at the first 's' in the previous index of the overall string if the
         * current index has an 's'. We also need to keep track of how many greedy algorithms
         * have started but haven't reached a 'b' yet, in case one shows up later, as well as
         * ensure that after we finish a full "bessie", we GO BACK to the "haven't started" state
         * again, just as we would in the O(n^2) correct-but-slow solution.
         * 
         * So, essentially, the solution is to iterate through the string t and for each index:
         * increment a counter of the # of greedy algorithms (which, to be clear, refer to each
         * pass through from the O(n2) solution) that have started, keep track of the number of
         * them that are currently finished with each possible prefix of the word "bessie" (6
         * indices plus 1 of "haven't even started the 'b'"), update this based on the letter
         * at the current index, multiply the number of greedies finished with the full "bessie"
         * by the number of indices on and to the right of the current index (and add that to
         * the answer), and move all the greedies fully done back to the "waiting for a 'b'"
         * state.
         */

        char[] t = br.readLine().toCharArray();
        int n = t.length;
        // numPasses[i] is the number of passes that have detected a prefix of "bessie" ending
        // at index i, where 1 <= i <= 6
        int[] numPasses = new int[7];
        char[] bessie = "xbessie".toCharArray();
        long ans = 0;
        for (int i = 0; i <= n-1; i++) {
            numPasses[0]++;
            for (int j = 6; j >= 1; j--) {
                if (t[i] == bessie[j]) {
                    numPasses[j] += numPasses[j-1];
                    numPasses[j-1] = 0;
                }
            }
            ans += numPasses[6] * (long) (n-1 - i + 1);
            numPasses[0] += numPasses[6];
            numPasses[6] = 0;
        }
        pw.println(ans);
    }

    // // // //

    static class Multiset { // ordered multiset
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }

    static class DSU {
        // disjoint-set/union-find data structure
        int[] parent;
        int[] size;

        public DSU(int length) {
            parent = new int[length];
            size = new int[length];
            for (int i = 0; i <= length - 1; i++) parent[i] = i;
            Arrays.fill(size, 1);
        }

        public int find(int x) {
            if (parent[x] == x) return x;
            else {
                parent[x] = find(parent[x]);
                return parent[x];
            }
        }

        public void union(int a, int b) {
            int c = find(a);
            int d = find(b);
            if (c != d) {
                int sum = size[c] + size[d];
                parent[d] = c;
                size[c] = sum;
                size[d] = sum;
            }
        }

        public int size(int x) {
            return size[x];
        }
    }

    static int gcd(int a, int b) {
        int B = Math.min(a, b);
        int A = Math.max(a, b);
        while (B != 0) {
            int temp = B;
            B = A % B;
            A = temp;
        }
        return A;
    }

    static ArrayList<Integer> primeFactorization(int n) {
        ArrayList<Integer> factors = new ArrayList<Integer>();
        for (int i = 2; i <= Math.sqrt(n); i++) {
            while (n % i == 0) {
                n /= i;
                factors.add(i);
            }
        }
        if (n != 1) {
            factors.add(n);
        }
        return factors;
    }

    static class SegmentTree {
        // this implementation is for doing range maximum queries by default
        // it's written recursively for now :|
        int[] f;
        int n;

        public SegmentTree(int[] original) {
            n = original.length;
            f = new int[4*n];

            build(original, 1, 0, n-1);
        }

        public void build(int[] a, int node, int tmpL, int tmpR) {
            if (tmpL == tmpR) {
                f[node] = a[tmpL];
            } else {
                int tmpM = (tmpL + tmpR) / 2;
                build(a, 2*node, tmpL, tmpM);
                build(a, 2*node+1, tmpM+1, tmpR);
                f[node] = Math.max(f[2*node], f[2*node+1]); // computes the higher-level node afterward
            }
        }

        public int query(int l, int r, int node, int tmpL, int tmpR) {
            if (l > r)
                return Integer.MIN_VALUE;
            if (tmpL == l && tmpR == r)
                return f[node];
            
            int tmpM = (tmpL + tmpR) / 2; // "temporary left", "temporary right", and "temporary mid"
            return Math.max(
                query(l, Math.min(r, tmpM), 2*node, tmpL, tmpM),
                query(Math.max(l, tmpM+1), r, 2*node+1, tmpM+1, tmpR)
            );
        }

        public int query(int l, int r) {
            // wrapper method
            return query(l, r, 1, 0, n-1);
        }

        public void update(int ind, int newVal, int node, int tmpL, int tmpR) {
            if (tmpL == tmpR) {
                f[node] = newVal;
            } else {
                int tmpM = (tmpL + tmpR) / 2;
                if (ind <= tmpM)
                    update(ind, newVal, 2*node, tmpL, tmpM);
                else
                    update(ind, newVal, 2*node+1, tmpM+1, tmpR);
                f[node] = Math.max(f[2*node], f[2*node+1]);
            }
        }

        public void update(int ind, int newVal) {
            update(ind, newVal, 1, 0, n-1);
        }
    }

    static long sqrt(long n) {
        // calculates the floor of sqrt(n) in O(log(n))
        if (n == 0) return 0;
        else if (n < 0) throw new IllegalArgumentException("can't return imaginary numbers");
        long l = 1, r = n, sqrt = -1;
        while (l <= r) {
            long mid = (l + r) / 2;
            long factor = n / mid;
            if (mid <= factor) {
                sqrt = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return sqrt;
    }

    static class Point {
        int i, j;

        public Point(int i, int j) {
            this.i = i;
            this.j = j;
        }

        // int x, y;

        // public Point(int x, int y) {
        //     this.x = x;
        //     this.y = y;
        // }
    }

    static class DSU2 {
        // 2-dimensional DSU
        Point[][] parent;
        int[][] size;

        public DSU2(int r, int c) {
            parent = new Point[r][c];
            size = new int[r][c];
            for (int i = 0; i <= r-1; i++) {
                for (int j = 0; j <= c-1; j++) {
                    parent[i][j] = new Point(i, j);
                }
            }
            for (int i = 0; i <= r-1; i++) {
                Arrays.fill(size[i], 1);
            }
        }

        public Point find(int i, int j) {
            if (parent[i][j].i == i && parent[i][j].j==j) {
                return parent[i][j];
            } else {
                parent[i][j] = find(parent[i][j].i, parent[i][j].j);
                return parent[i][j];
            }
        }

        public void union(int ai, int aj, int bi, int bj) {
            Point c = find(ai, aj);
            Point d = find(bi, bj);
            if (c.i != d.i || c.j != d.j) {
                int sum = size[c.i][c.j] + size[d.i][d.j];
                parent[d.i][d.j] = c;
                size[c.i][c.j] = sum;
                size[d.i][d.j] = sum;
            }
        }

        public int size(int i, int j) {
            return size[i][j];
        }
    }

    static long taxiDist(long x1, long y1, long x2, long y2) {
        // Manhattan distance between two points in the Cartesian coordinate plane
        return Math.abs(x2 - x1) + Math.abs(y2 - y1);
    }

    static double dist(long x1, long y1, long x2, long y2) {
        // uses the Pythagorean theorem to calculate the distance between two points
        // in the Cartesian coordinate plane
        long a = x2 - x1;
        long b = y2 - y1;
        return Math.sqrt(Math.pow(a, 2) + Math.pow(b, 2));
        // return (long) (Math.pow(a, 2) + Math.pow(b, 2)); // to return squared distance
    }

    static <T> void generatePermutations(int k, T[] a) {
        if (k == 1) {
            System.out.println(Arrays.toString(a)); // change this to whatever is considered as outputting the permutation
        } else {
            generatePermutations(k-1, a);
            for (int i = 0; i <= k-2; i++) {
                if (k % 2 == 0) {
                    T temp = a[i];
                    a[i] = a[k-1];
                    a[k-1] = temp;
                } else {
                    T temp = a[0];
                    a[0] = a[k-1];
                    a[k-1] = temp;
                }
                generatePermutations(k-1, a);
            }
        }
    }
}


// import java.util.*;
// import java.io.*;

// public class Pareidolia {
//     public static void main(String[] args) throws IOException {
//         BufferedReader br = new BufferedReader(new FileReader("./prob3_silver_open23/6.in"));
//         PrintWriter pw = new PrintWriter(System.out);

//         // char[] t = br.readLine().toCharArray();
//         // char[] bessie = {'b', 'e', 's', 's', 'i', 'e'};
//         // int[] letterCount = new int[6];
//         // int j = 0;
//         // long count = 0;
//         // for (int i = 0; i <= t.length-1; i++) {
//         //     if (t[i]==bessie[j]) {
//         //         letterCount[j]++;
//         //         count += letterCount[5];
//         //         j = (j+1)%6;
//         //     }
//         // }
//         // letterCount = new int[6];
//         // j = 5;
//         // for (int i = t.length-1; i >= 0; i--) {
//         //     if (t[i] == bessie[j]) {
//         //         letterCount[j]++;
//         //         count += letterCount[0];
//         //         j = j==0?5:j-1;
//         //     }
//         // }
//         // pw.print(count);

//         char[] t = br.readLine().toCharArray();
//         char[] bessie = "bessie".toCharArray();
//         int j = 0;
//         TreeSet<Long> endpoints = new TreeSet<Long>();
//         for (int i = 0; i <= t.length-1; i++) {
//             if (t[i]==bessie[j]) {
//                 if (j==5) {
//                     endpoints.add((long)i);
//                 }
//                 j = (j+1)%6;
//             }
//         }
//         j = 5;
//         for (int i = t.length-1; i >= 0; i--) {
//             if (t[i]==bessie[j]) {
//                 if (j==0) {
//                     endpoints.add((long)i);
//                 }
//                 j = j==0?5:j-1;;
//             }
//         }

//         long ans = 0;
//         while (!endpoints.isEmpty()) {
//             long start = endpoints.pollFirst();
//             long end = endpoints.pollFirst();
//             // if (!(start.type.equals("start") && end.type.equals("end"))) {
//             //     throw new IllegalArgumentException();
//             // }
//             ans += (long)(start+1) * (long)(t.length-end);
//         }
//         pw.print(ans);

//         br.close(); pw.close();

//         // first assume that we are not looking over all substrings but rather all prefixes, and
//         // checking the sum of B(s) for all of those prefixes. consider a subsequence of the string
//         // that contains one bessie. it is obvious that all prefixes that are a superstring of that
//         // prefix (i.e. are that prefix or are longer) will also contain that one bessie, although
//         // they may also contain more.
//         // at each point in the string, we can consider to see how many total substrings there are
//     }
    
//     // static class Thing implements Comparable<Thing> {
//     //     int index;
//     //     String type;

//     //     public Thing(int index, String type) {
//     //         this.index = index;
//     //         this.type = type;
//     //     }

//     //     public int compareTo(Thing other) {
//     //         return Integer.compare(this.index, other.index);
//     //     }
//     // }
// }

// // import java.io.BufferedReader;
// // import java.io.IOException;
// // import java.io.InputStreamReader;
// // import java.util.Arrays;
 
// // public class Pareidolia {
 
// //     public static void main(String[] args) throws IOException {
// //         BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
// //         String string = in.readLine();
// //         long answer = 0;
// //         long[] waiting = new long[7];
// //         long rem = string.length();
// //         System.out.println("\nwaiting = " + Arrays.toString(waiting));
// //         System.out.println("rem is initially = " + rem + "\n");
// //         for (char letter : string.toCharArray()) {
// //             System.out.println("    letter = "+letter);
// //             waiting[0]++;
// //             System.out.println("waiting after incrementing waiting[0] = "+Arrays.toString(waiting));
// //             for (int d = 5; d >= 0; d--) {
// //                 if (letter == "bessie".charAt(d)) {
// //                     waiting[d + 1] += waiting[d];
// //                     waiting[d] = 0;
// //                 }
// //             }
// //             System.out.println("waiting after going trhough a loop of 6 = "+Arrays.toString(waiting));
// //             answer += waiting[6] * rem;
// //             waiting[0] += waiting[6];
// //             waiting[6] = 0;
// //             rem--;
// //             System.out.println("rem is now = "+rem);
// //             System.out.println("waiting at end of current iteration of loop = "+Arrays.toString(waiting));
// //             System.out.println("ans = " + answer);
// //             System.out.println();
// //         }
// //         System.out.println(answer);
// //     }
// // }