import java.util.*;
import java.io.*;

public class ElementaryParticles {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            ArrayList<Integer>[] positions = new ArrayList[150000];
            for (int i = 0; i <= 149999; i++) positions[i] = new ArrayList<>();
            for (int i = 0; i <= n-1; i++) {
                positions[a[i]-1].add(i);
            }

            int max = -1;
            for (ArrayList<Integer> list : positions) {
                if (list.size()>=2) {
                    for (int i = 0; i <= list.size()-2; i++) {
                        int l = list.get(i);
                        int r = list.get(i+1);
                        max = Math.max(max, n-r+l);
                    }
                }
            }
            pw.println(max);
        }

        br.close(); pw.close();
    }
}
