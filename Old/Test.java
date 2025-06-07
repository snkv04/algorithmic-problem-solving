import java.util.*;
import java.time.*;
import java.io.*;

public class Test {
    static BufferedReader br;
    static PrintWriter pw;
    static int[] di = new int[] {0, 0, 1, -1},
        dj = new int[] {1, -1, 0, 0};

    public static void main (String[] args) throws IOException {
        br = new BufferedReader(new FileReader("testtext.txt"));
        pw = new PrintWriter(System.out);

        // String a = "hello";
        // String b = "hi";
        // b = a;
        // System.out.println(a + " " + b);
        // a = "wassup";
        // System.out.println(a + " " + b);
        // a="";
        // b = a;
        // b="qwerty";
        // System.out.println(a + " " + b);
        // // int a = Integer.MAX_VALUE;
        // // System.out.println(a);
        // // a ++;
        // // System.out.println(a);
        // boolean[] a = {false, false, false, false, false, false, true, true, true, true};
        // int low = 0, high = 9, answer = -1;
        // while(low <= high) {
        //     int mid = (low + high) / 2;
        //     if (a[mid]) {
        //         high = mid-1;
        //         answer=mid;
        //     } else {
        //         low = mid+1;
        //     }
        // }
        // System.out.println(answer);
        // System.out.println('E'>='B');
        // System.out.println(primeFactorization(100));
        // System.out.println(primeFactorization(252));
        // boolean[] t = new boolean[1000000000];
        // char[] te = new char[1000000000];
        // int[] testing = new int[1000000000];
        // LocalTime before = LocalTime.now();
        // LocalTime after = LocalTime.now();
        // System.out.println("before = " + before);
        // System.out.println("after = " + after);
        // String[][] test = new String[4][4];
        // for (int i =0; i<=3;i++){
        //     for (int j=0;j<=3;j++) {
        //         test[i][j]=""+(4-i)+""+j;
        //     }
        // }

        // // for (int i =0; i<=3; i++) {
        // //     for (int j=0; j<=3; j++) {
        // //         System.out.print(test[i][j] + " ");
        //     }
        //     System.out.println();
        // }
        // System.out.println();

        // Arrays.sort(test, Comparator.comparing((String[] obj) -> obj[0]));
        // for (int i =0; i<=3; i++) {
        //     for (int j=0; j<=3; j++) {
        //         System.out.print(test[i][j] + " ");
        //     }
        //     System.out.println();
        // }
        // System.out.println();
        // System.out.println(7);
        // System.out.println(7<<3);
        // System.out.println(9>>1);
        // System.out.println(17>0);
        // long max = 1;
        // for (int i = 1; i <= 12; i++) {
        //     max *= 10;
        // }
        // System.out.println(max);
        // // for (long i = 1; i <= max; i++) {
        // //     System.out.println(i);
        // // }
        // System.out.println(5.7 % 1 == 0);
        // System.out.println(5.7 % 1);
        // System.out.println(5.7 % 5 == 0);
        // System.out.println(5.7 % 5);
        // System.out.println(5 % 5 == 0);
        // System.out.println(5 % 5);
        // System.out.println(5.0 % 5 == 0);
        // System.out.println(5.0 % 5);
        // System.out.println(5.00000000000000000001 % 1 == 0);
        // System.out.println(5.00000000000000000001 % 1);
        // System.out.println(5.00000000000000000000 % 1 == 0);
        // System.out.println(5.00000000000000000000 % 1);

        // HashSet<Thing> set = new HashSet<>();
        // for (int i = 1; i <= 10; i++) {
        //     set.add(new Thing(i, i+1, (i+2)+""));
        // }
        // System.out.println(set);

        // int a = 1;
        // for (Thing t : set) {
        //     if (a <= 6) {
        //         t.x -= 17;
        //         t.str = "hello";
        //     }
        //     a++;
        // }
        // System.out.println(set);
        // int[] ar = new int[100000000];
        // for (int i = 1; i <= 99999999; i++) {
        //     ar[i] = ar[i-1]+1;
        //     System.out.println(ar[i]);
        // }
        // System.out.println(Arrays.toString(ar));
        // System.out.println(Arrays.toString("asdfasdf".split("")));
        // System.out.println((int)'A'  );
        // System.out.println(1<<31-1);
        // int a, b, c;
        // a = b = c = 7;
        // System.out.println(a + " " + b + " " + c);

        // System.out.println(Math.pow(2000000000, 2));
        // System.out.println((long) (5.0e23));
        // System.out.println(Integer.toBinaryString(453+(2<<7)));
        // for (int i = 453; i <= 100000; i++) {
        //     System.out.println("i="+i+", and and = "+(453&i));
        //     if ((i & (1<<7)) ==0) break;
        // }
        // System.out.println((2<<29)+1);
        // LocalTime before = LocalTime.now();
        // PrintWriter pw = new PrintWriter(System.out);
        // for (int i = 1; i <= 1000000; i++) {
            // pw.println("i = "+i);
        // }
        // LocalTime after = LocalTime.now();
        // pw.println("before = " + before);
        // pw.println("after = " + after);
        // pw.close();

        // long c = 0;
        // long num = 1000000*(long)1000000;
        // for (long i = 1; c <= num; i++) {
        //     c+=i;
        //     System.out.println("i = "+i+", c = "+c);
        // }
        // pw.println(((-20)%16));
        // pw.close();

        // PriorityQueue<Integer> pq = new PriorityQueue<>();
        // for (int i = 1; i <= 20; i++) {
        //     pq.add((int)(Math.random()*100+1));
        // }
        // System.out.println(pq);
        // while (!pq.isEmpty()) {
        //     System.out.println();
        //     System.out.println(pq.poll());
        //     System.out.println(pq);
        // }
        // System.out.println((long)1<<40);

        // double n = -1;
        // System.out.println("n="+n);
        // for (int i = 1; i <= 320; i++) {
        //     n *= 10;
        //     System.out.println("i = "+i+", n = "+n);
        // }
        // // for (int i = 1; i <= 40; i++) {
        // //     n /= 10;
        // //     System.out.println("i="+i+", n="+n);
        // // }

        // System.out.println(Math.pow(17, 1.0/15));
        // System.out.println((int)7.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999);

        // Thing t = new Thing(1, 2, "a");
        // HashSet<Thing> set = new HashSet<>();
        // set.add(new Thing(1, 1, "A"));
        // set.add(new Thing(1, 1, "A"));
        // set.add(t); set.add(t); set.add(t);
        // System.out.println(set);

        // long number = Long.parseLong("2569144112553501657");
        // Stack<Integer> s = new Stack<>();
        // while (number != 0) {
        //     s.add((int)(number%2));
        //     number /= 2;
        // }
        // while (!s.isEmpty()) {
        //     System.out.print(s.pop());
        // }
        // System.out.println();

        // double a = 1;
        // for (int i = 1; i <= 350; i++) {
        //     a *= 10;
        //     System.out.println("10^"+i+" = "+a);
        // }


        // String s = br.readLine();
        long before = System.currentTimeMillis();
        // String[] arr = s.split(" ");
        // for (int i = 0; i <= arr.length-1; i++) pw.println(arr[i]);
        for (int i = 1; i <= 100000000; i++) {
            pw.println();
            // ;
        }
        long after = System.currentTimeMillis();
        long duration = after - before;
        pw.println("duration = " + duration);
        
        // before = LocalTime.now();
        // StringTokenizer st = new StringTokenizer(s);
        // while (st.hasMoreTokens()) pw.println(st.nextToken());
        // after = LocalTime.now();
        // String output2 = "before="+before+", after="+after;

        // pw.println(output);
        // pw.println(output2);
        
        // pw.println("before = " + before);
        // pw.println("after = " + after);

        // pw.println(primeFactorization(1048596));



        // pw.println((-9)%7);
        // double val = 1.234567890123456789012345678901234567890;
        // for (int i = 1; i <= 300; i++) {
        //     val *= 10.0;
        // }
        // for (int i = 1; i <= 300; i++) {
        //     val /= 10.0;
        // }
        // pw.println(val);

        // int n = 19;
        // int[][] grid = new int[n][n];
        // Stack<Pair> q = new Stack<>();
        // q.add(new Pair(n/2, n/2));
        // grid[n/2][n/2] = 1;
        // while (!q.isEmpty()) {
        //     Pair p = q.pop();
        //     for (int k = 0; k <= 3; k++) {
        //         int i = p.a + di[k];
        //         int j = p.b + dj[k];
        //         if (i <= n-1 && i >= 0 && j >= 0 && j <= n-1 && grid[i][j] == 0) {
        //             grid[i][j] = grid[p.a][p.b] + 1;
        //             q.add(new Pair(i, j));
        //         }
        //     }
        // }
        // for (int i = 0; i <= n-1; i++) {
        //     // pw.println(Arrays.toString(grid[i]));
        //     for (int j = 0; j <= n-1; j++) {
        //         pw.print(String.format("%3d, ", grid[i][j]));
        //     }
        //     pw.println();
        // }

        // hello(new Stack<Integer>());

        // StringTokenizer st = new StringTokenizer("aassdfasdfasdfffffasdf\nhello", "\ns");
        // while (st.hasMoreTokens()) {
        //     pw.println("|"+st.nextToken()+"|");
        // }

        // Thing[] arr = new Thing[10];
        // System.out.println(Arrays.toString(arr));

        br.close();
        pw.close();
    }

    static void hello(Stack<Integer> s) {
        if (s.size()==10) return;

        s.add(s.isEmpty()?1:s.peek()+1);
        hello(s);
        s.pop();

        pw.println(s);
    }

    static class Thing {
        int x, y;
        String str;

        public Thing(int x, int y, String s) {
            this.x = x;
            this.y = y;
            this.str = s;
        }

        public String toString() {
            return "(x="+x+", y="+y+", str="+str+")";
        }
    }

    static ArrayList<Edge> edges;
    public static void bellman_ford(int start) {

    }

    static class Edge {
        int from, to, weight;
        public Edge(int from, int to, int weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }
    }

    static ArrayList<Integer> primeFactorization(int n) {
        ArrayList<Integer> factors = new ArrayList<Integer>();
        for (int i = 2; i <= Math.sqrt(n); i++) {
            while (n % i == 0) {
                n /= i;
                factors.add(i);
            }
            System.out.println(i);
        }
        if (n != 1) {
            factors.add(n);
        }
        return factors;
    }

    static class Pair {
        int a, b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}
