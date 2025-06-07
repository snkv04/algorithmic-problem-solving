import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class MengerSponge {
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
         * at each iteration, divide the current thing into 27 subcubes. if the current coords are not in
         * the subcubes, then we're done. otherwise, identify which subcube we're in. expand this current
         * subcube to be the original size, and then map the coordinates into the new space. repeat.
         * 
         * special cases:
         * on a corner: always good
         * on an edge: bad if it's one of the center ones
         * on a face: bad if it's a center face, or extended out from a center face
         */
        String[] s = br.readLine().split(" ");
        long L = Long.parseLong(s[0]),
            xn = Long.parseLong(s[1]),
            xd = Long.parseLong(s[2]),
            yn = Long.parseLong(s[3]),
            yd = Long.parseLong(s[4]),
            zn = Long.parseLong(s[5]),
            zd = Long.parseLong(s[6]);
        Frac[] xyz = new Frac[3];
        xyz[0] = new Frac(xn, xd);
        xyz[1] = new Frac(yn, yd);
        xyz[2] = new Frac(zn, zd);

        for (int currLevel = 1; currLevel <= L; currLevel++) {
            /*
             * we can check if it's contained in one of the 20 good sponges. if it's contained in 2 of them,
             * then it won't change the answer, so we can pick arbitrarily.
             * if we find one that it's contained in, then resize. if not, then we're done.
             */
            boolean wasContained = false;
            for (int i = 0; i <= 2 && !wasContained; i++) {
                for (int j = 0; j <= 2 && !wasContained; j++) {
                    for (int k = 0; k <= 2; k++) {
                        int countOdd = 0;
                        countOdd += (i==1)?1:0;
                        countOdd += (j==1)?1:0;
                        countOdd += (k==1)?1:0;
                        if (countOdd >= 2) continue; // not considering the sponges removed in this level

                        Frac xmin = new Frac(i, 3), xmax = new Frac(i+1, 3),
                            ymin = new Frac(j, 3), ymax = new Frac(j+1, 3),
                            zmin = new Frac(k, 3), zmax = new Frac(k+1, 3);
                        
                        if (xyz[0].compareTo(xmin)>=0 && xyz[0].compareTo(xmax) <= 0
                            && xyz[1].compareTo(ymin)>=0 && xyz[1].compareTo(ymax)<=0
                            && xyz[2].compareTo(zmin)>=0 && xyz[2].compareTo(zmax) <= 0) {

                            wasContained = true;
                            for (int dim = 0; dim <= 2; dim++) {
                                Frac min;
                                if (dim == 0) {
                                    min = xmin;
                                } else if (dim == 1) {
                                    min = ymin;
                                } else {
                                    min = zmin;
                                }
                                xyz[dim] = xyz[dim].subtract(min);
                                xyz[dim].n *= 3;
                                xyz[dim] = xyz[dim].reduce();
                            }
                            break;
                        }
                    }
                }
            }

            if (!wasContained) {
                pw.println(0);
                return;
            }
        }
        pw.println(1);
    }

    static class Triple {
        int i, j, k;

        public Triple(int i, int j, int k) {
            this.i = i;
            this.j = j;
            this.k = k;
        }
    }

    static class Frac implements Comparable<Frac> {
        long n, d;

        public Frac(long n, long d) {
            this.n = n;
            this.d = d;
        }

        public int compareTo(Frac other) {
            long lcm = this.d * other.d / gcd(this.d, other.d);
            long newn = this.n * lcm / this.d;
            long newothern = other.n * lcm / other.d;
            return Long.compare(newn, newothern);
        }

        public Frac subtract(Frac other) {
            long lcm = this.d * other.d / gcd(this.d, other.d);
            long newn = this.n * lcm / this.d;
            long newothern = other.n * lcm / other.d;
            newn -= newothern;
            
            Frac result = new Frac(newn, lcm);
            return result.reduce();
        }

        public Frac reduce() {
            long gcd = gcd(this.n, this.d);
            return new Frac(this.n / gcd, this.d / gcd);
        }

        public String toString() {
            return this.n+"/"+this.d;
        }
    }

    static long gcd(long a, long b) {
        long B = Math.min(a, b);
        long A = Math.max(a, b);
        while (B != 0) {
            long temp = B;
            B = A % B;
            A = temp;
        }
        return A;
    }
}
