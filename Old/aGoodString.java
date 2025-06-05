import java.util.*;
import java.io.*;

public class aGoodString {
    static int n, exp;
    static char[] s;
    static ArrayList<Integer>[] counts;
    static int[][] prefsums;
    
    // public static void main(String[] args) throws IOException {
    //     BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    //     PrintWriter pw = new PrintWriter(System.out);

    //     int t = Integer.parseInt(br.readLine());
    //     while (t-->0) {
    //         n = Integer.parseInt(br.readLine());
    //         s = br.readLine().toCharArray();
    //         if (n==1) {
    //             if (s[0]=='a') pw.println(0);
    //             else pw.println(1);
    //             continue;
    //         }
    //         exp = 0;
    //         while ((1<<(exp+1))<=n) {
    //             exp++;
    //         }
    //         counts = new ArrayList[exp];
    //         for (int i = 0; i <= exp-1; i++) { counts[i] = new ArrayList<>(); counts[i].add(-1); }
    //         for (int i = 0; i <= exp-1; i++) {
    //             char letter = (char)('a'+i);
    //             int size = 0;
    //             int count = 0;
    //             for (int j = 0; j <= n-1; j++) {
    //                 if (s[j]!=letter) {
    //                     count++;
    //                 }
    //                 size++;
    //                 if (size == (1<<(exp-1-i))) {
    //                     counts[i].add(count);
    //                     count = 0; size = 0;
    //                 }
    //             }
    //         }
    //         // for (int i = 0; i <= exp-1; i++) {pw.println(i + " "+counts[i]);}

    //         int min = (int)2e5+6;
    //         for (int i = 1; i <= n; i++) {
    //             min = Math.min(min, traverse(i));
    //         }
    //         pw.println(min);
    //     }

    //     br.close(); pw.close();
    // }

    // static int traverse(int index) {
    //     int cost = 0;
    //     if (s[index-1] != (char)('a'+exp)) cost++;
    //     for (int i = exp-1; i >= 0; i--) {
    //         if (index%2==1) index++;
    //         else index--;
    //         cost += counts[i].get(index);
    //         index = (index+1)/2;
    //     }
    //     return cost;
    // }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            n = Integer.parseInt(br.readLine());
            s = br.readLine().toCharArray();
            exp = 0;
            while ((1<<(exp+1))<=n) {
                exp++;
            }

            prefsums = new int[exp][n+1];
            for (char letter = 'a'; letter <= (char)('a'+exp-1); letter++) {
                for (int i = 1; i <= n; i++) {
                    prefsums[letter-'a'][i] = prefsums[letter-'a'][i-1] + (s[i-1]==letter?0:1);
                }
            }

            pw.println(cost('a', 1, n));
        }

        br.close(); pw.close();
    }

    static int cost(char c, int l, int r) {
        if (l==r) return s[l-1]==c?0:1;
        int mid = (l+r)/2;
        int chooseLeft = prefsums[c-'a'][mid]-prefsums[c-'a'][l-1] + cost((char)(c+1), mid+1, r);
        int chooseRight = prefsums[c-'a'][r]-prefsums[c-'a'][mid] + cost((char)(c+1), l, mid);
        return Math.min(chooseLeft, chooseRight);
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
}
