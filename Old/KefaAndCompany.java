import java.util.*;
import java.io.*;

public class KefaAndCompany {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int d = Integer.parseInt(line[1]);
        Friend[] friends = new Friend[n];
        for (int i = 0; i <= n-1; i++) {
            line = br.readLine().split(" ");
            int m = Integer.parseInt(line[0]);
            int s = Integer.parseInt(line[1]);
            friends[i] = new Friend(m, s);
        }
        Arrays.sort(friends);

        long max = friends[0].value, curr = friends[0].value;
        int i = 0, j = 0;
        while (j <= n-2) {
            if (friends[j+1].money < friends[i].money+d) {
                j++;
                curr += friends[j].value;
            } else {
                if (i==j) {
                    i++;
                    j++;
                    curr = friends[i].value;
                } else {
                    curr -= friends[i].value;
                    i++;
                }
            }
            max = Math.max(max, curr);
        }
        pw.println(max);

        br.close(); pw.close();
    }

    static class Friend implements Comparable<Friend> {
        int money, value;

        public Friend(int money, int value) {
            this.money = money;
            this.value = value;
        }

        public int compareTo(Friend other) {
            if (this.money != other.money) return Integer.compare(this.money, other.money);
            else return Integer.compare(this.value, other.value);
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
