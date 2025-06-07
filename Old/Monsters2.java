import java.util.*;
import java.io.*;

public class Monsters2 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            TreeSet<Monster> monsters = new TreeSet<>();
            ArrayList<Integer> order = new ArrayList<Integer>();
            for (int i = 1; i <= n; i++) {
                int hp = sc.nextInt();
                if (hp%k==0) {
                    order.add(i);
                } else{
                    monsters.add(new Monster(hp % k, i));
                }
            }
            
            while (!monsters.isEmpty()) {
                order.add(monsters.pollLast().ind);
            }
            for (int position : order) pw.print(position + " ");
            pw.println();
        }

        sc.close(); pw.close();
    }

    static class Monster implements Comparable<Monster> {
        int hp, ind;

        public Monster(int hp, int ind) {
            this.hp = hp;
            this.ind = ind;
        }

        public int compareTo(Monster other) {
            if (this.hp != other.hp) return Integer.compare(this.hp, other.hp);
            else return -Integer.compare(this.ind, other.ind);
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
