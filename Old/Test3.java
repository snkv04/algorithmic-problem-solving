import java.util.*;
import java.io.*;

public class Test3 {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        // int n = Integer.parseInt(br.readLine());
        // pw.println(String.format("%04d", n));
        // pw.println(Integer.parseInt(String.format("%04d", n)));

        // Random random = new Random();
        // int[] a = new int[64];
        // for (int i = 0; i <= 63; i++) a[i] = random.nextInt(100);
        // pw.println(Arrays.toString(a));
        // insertionSort(a, 64);
        // pw.println(Arrays.toString(a));
        // for (int i = 0; i <= 62; i++) {
        //     if (a[i+1] < a[i]) {
        //         pw.println("error at a["+i+"] = "+a[i]+" and a["+(i+1)+"] = "+a[i+1]);
        //     }
        // }

        // char c = 'c';
        // pw.println(c - 'a');

        int[] a = {5,5,4,3,2,2};
        int n = a.length;
        Stack<Integer> monotonic = new Stack();
        int[] rangeRight = new int[n];
        for (int i = 0; i <= n; i++) {
            int currVal = i==n ? 0 : a[i];
            while (!monotonic.isEmpty() && a[monotonic.peek()] > currVal) {
                int idx = monotonic.pop();
                rangeRight[idx] = i-1;
            }
            monotonic.add(i);
        }
        pw.println(Arrays.toString(a));
        pw.println(Arrays.toString(rangeRight));

        br.close(); pw.close();
    }

    public static void insertionSort(int[] a, int dataLength) throws IOException {
    	for (int i = 1; i <= dataLength - 1; i++) {
    		int j = i - 1;
    		int inserting = a[i];
    		int pushingRight = a[j];
    		
    		while (j >= 0) {
    			if (inserting >= pushingRight) {
    				break;
    			}
    			
    			a[j+1] = pushingRight;
    			a[j] = inserting;
    			j--;
    			if (j >= 0) pushingRight = a[j];
    		}
    	}
    }
}
