import java.util.*;
import java.io.*;
 
public class BinaryStringCopying {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
 
        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            char[] s = br.readLine().toCharArray();
            
            int[] next1 = new int[n];
            next1[n-1] = n-1;
            for (int i = n-2; i >= 0; i--) {
                next1[i] = s[i]=='0' ? next1[i+1] : i;
            }
            int[] last0 = new int[n];
            last0[0] = 0;
            for (int i = 1; i <= n-1; i++) {
                last0[i] = s[i]=='1' ? last0[i-1] : i;
            }
 
            TreeSet<Segment> changes = new TreeSet<>();
            for (int i = 1; i <= m; i++) {
                line = br.readLine().split(" ");
                int l = Integer.parseInt(line[0])-1;
                int r = Integer.parseInt(line[1])-1;
                // if (l==r) {
                //     l=-1;r=-1;
                // } else {
                    r = last0[r];
                    l = next1[l];
                    if (r <= l) { l=-1;r=-1; }
                // }
 
                changes.add(new Segment(l, r));
            }
            pw.println(changes.size());
        }
 
        br.close(); pw.close();
    }
 
    static class Segment implements Comparable<Segment> {
        int leftBound, rightBound;
 
        public Segment(int left, int right) {
            this.leftBound = left;
            this.rightBound = right;
        }
 
        public int compareTo(Segment other) {
            if (this.leftBound != other.leftBound)
                return Integer.compare(this.leftBound, other.leftBound);
            else return Integer.compare(this.rightBound, other.rightBound);
        }
 
        public String toString() {
            return "(start="+leftBound+", end="+rightBound+")";
        }
    }
}