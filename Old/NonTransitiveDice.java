import java.io.*;

public class NonTransitiveDice {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for(int i = 1; i <= t; i++) {
            String[] split = br.readLine().split(" ");
            int[] d1 = new int[4], d2 = new int[4];
            for(int j = 0; j <= 3; j++) {
                d1[j] = Integer.parseInt(split[j]);
                d2[j] = Integer.parseInt(split[j+4]);
            }

            boolean nonTransitiveSet = false;
            for(int side1 = 1; side1 <= 10; side1++) {
                for(int side2 = 1; side2 <= 10; side2++) {
                    for(int side3 = 1; side3 <= 10; side3++) {
                        for(int side4 = 1; side4 <= 10; side4++) {
                            if(isNonTransitive(d1, d2, new int[] {side1, side2, side3, side4})) {
                                nonTransitiveSet = true;
                                break;
                            }
                        }
                        if(nonTransitiveSet) break;
                    }
                    if(nonTransitiveSet) break;
                }
                if(nonTransitiveSet) break;
            }

            if(nonTransitiveSet) pw.println("yes");
            else pw.println("no");
        }

        br.close(); pw.close();
    }

    // static class Die {
    //     int a, b, c, d;

    //     public Die(int a, int b, int c, int d) {
    //         this.a = a;
    //         this.b = b;
    //         this.c = c;
    //         this.d = d;
    //     }
    // }
    // can just use an array instead of a Die class

    static boolean isNonTransitive(int[] a, int[] b, int[] c) {
        if(beats(a, b) == 1 && beats(b, c) == 1 && beats(c, a) == 1) {
            return true;
        } else if(beats(a, b) == -1 && beats(b, c) == -1 && beats(c, a) == -1) {
            return true;
        } else {
            return false;
        }
    }

    static int beats(int[] a, int[] b) {
        int firstWins = 0;
        int secondWins = 0;
        for(int i = 0; i <= 3; i++) {
            for(int j = 0; j <= 3; j++) {
                if(a[i] > b[j]) firstWins++;
                else if (a[i] < b[j]) secondWins++;
            }
        }

        if(firstWins > secondWins) {
            // returns 1 if the first die, a, beats the second die, b
            return 1;
        } else if(secondWins > firstWins) {
            return -1;
        } else return 0;
    }
}