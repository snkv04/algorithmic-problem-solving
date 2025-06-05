import java.util.*;
import java.io.*;

public class CircularBarn2 {
    private static final TreeSet<Integer> primes = getPrimeList();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            System.out.println("now entering test case"+i); // DELEETE
            int n = Integer.parseInt(br.readLine());
            int[] cows = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            pw.println(playGame(n, cows));
        }

        br.close(); pw.close();
    }

    public static String playGame(int n, int[] cows) {
        /*
         * go through each barn in the circle
         * remove the maximum prime beneath it
         * if 0, then john wins
         * if not, remove the greatest prime beneath it
         * if 0, then nhoj wins
         * if still not 0, then go to the next barn
         * if none became 0 yet, then go back to beginning of barn
         */

        System.out.println("now in playgame"); //delete

        while (true) {
            for (int i = 0; i <= n-1; i++) {
                System.out.println("current array: "+ Arrays.toString(cows));
                System.out.println("i is equal to: "+i);

                if (cows[i] == 0) return "Farmer Nhoj";
                System.out.println("john didn't lose. now john takes out "+findGreatestPrime(cows[i])+" cows");
                cows[i] = cows[i] - findGreatestPrime(cows[i]);
                System.out.println("there are now "+cows[i]+" cows at array index "+i);
                if (cows[i] == 0) return "Farmer John";
                System.out.println("nhoj didn't lose. now nhoj takes out "+findGreatestPrime(cows[i])+" cows");
                cows[i] = cows[i] - findGreatestPrime(cows[i]);
                System.out.println("there are now "+cows[i]+" cows at array index "+i);
            }
        }
    }

    public static int findGreatestPrime(int n) {
        return primes.floor(n);
    }

    public static TreeSet<Integer> getPrimeList() {
        // also includes 1 in the TreeSet
        TreeSet<Integer> primes = new TreeSet<Integer>();
        primes.add(1);
        for (int i = 2; i <= 500000; i++) {
            boolean isPrime = true;
            for (int j = 2; j <= i-1; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) primes.add(i);
        }
        return primes;
    }
}
