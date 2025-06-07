import java.util.*;
import java.io.*;

public class WhyCowCrossRoad {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("helpcross.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("helpcross.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int c = Integer.parseInt(line[0]);
        int n = Integer.parseInt(line[1]);
        ArrayList<Integer> chickens = new ArrayList<Integer>();
        for(int i = 1; i <= c; i++) {
            chickens.add(Integer.parseInt(br.readLine()));
        }
        ArrayList<Cow> cows = new ArrayList<Cow>();
        for (int i = 1; i <= n; i++) {
            int[] cowLine = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            cows.add(new Cow(cowLine[0], cowLine[1]));
        }
        chickens.sort(Comparator.naturalOrder());
        cows.sort(new Comp());

        int count = 0;
        for (int i = 0; i <= c-1; i++) {
            int chicken = chickens.get(i);
            for (int j = 0; j <= cows.size()-1; j++) {
                if (cows.get(j).a <= chicken && chicken <= cows.get(j).b) {
                    count++;
                    cows.remove(j);
                    break;
                }
            }
        }
        pw.print(count);

        br.close(); pw.close();
    }

    static class Cow {
        int a;
        int b;

        public Cow(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

    static class Comp implements Comparator<Cow> {
        public int compare(Cow c1, Cow c2) {
            if (c1.b != c2.b) {
                return Integer.compare(c1.b, c2.b);
            } else {
                return Integer.compare(c1.a, c2.a);
            }
        }
    }
}
