import java.util.*;
import java.io.*;

public class CharacterBlocking {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int T = Integer.parseInt(br.readLine());
        while (T-->0) {
            char[][] s = new char[3][0];
            s[1] = br.readLine().toCharArray();
            s[2] = br.readLine().toCharArray();
            String[] line = br.readLine().split(" ");
            int t = Integer.parseInt(line[0]);
            int q = Integer.parseInt(line[1]);

            int n = s[1].length;
            int matching = 0, unblocked=n;
            for (int i = 0; i <= n-1; i++) {
                if (s[1][i]==s[2][i]) matching++;
            }

            Queue<Pair> blocked = new LinkedList<Pair>();
            for (int i = 1; i <= q; i++) {
                if (!blocked.isEmpty() && blocked.peek().time==i) {
                    // unblocks that character
                    Pair beingUnblocked = blocked.poll();
                    unblocked++;
                    if (s[1][beingUnblocked.ind] == s[2][beingUnblocked.ind]) {
                        matching++;
                    }
                }

                line = br.readLine().split(" ");
                if (Integer.parseInt(line[0])==1) {
                    int beingBlocked = Integer.parseInt(line[1])-1;
                    blocked.add(new Pair(beingBlocked, i+t));
                    if (s[1][beingBlocked]==s[2][beingBlocked]) matching--;
                    unblocked--;
                } else if (Integer.parseInt(line[0])==2) {
                    int string1 = Integer.parseInt(line[1]);
                    int string2 = Integer.parseInt(line[3]);
                    int pos1 = Integer.parseInt(line[2])-1;
                    int pos2 = Integer.parseInt(line[4])-1;
                    int count1 = 0;
                    if (s[1][pos1]==s[2][pos1])count1++;
                    if(s[1][pos2]==s[2][pos2])count1++;

                    char temp = s[string1][pos1];
                    s[string1][pos1] = s[string2][pos2];
                    s[string2][pos2] = temp;

                    int count2 = 0;
                    if (s[1][pos1]==s[2][pos1])count2++;
                    if(s[1][pos2]==s[2][pos2])count2++;
                    matching += count2-count1;
                } else {
                    pw.println(matching==unblocked?"YES":"NO");
                }
            }
        }

        br.close(); pw.close();
    }

    static class Pair {
        int ind, time;

        public Pair(int ind, int time) {
            this.ind = ind;
            this.time = time;
        }
    }

    // // // //

    static class Multiset {
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
}
