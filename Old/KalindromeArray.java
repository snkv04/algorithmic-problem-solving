import java.util.*;
import java.io.*;

public class KalindromeArray {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int delete1=-1, delete2=-1;
            for (int i = 0; i <= (n-1)/2; i++) {
                if (a[i] != a[n-1-i]) {
                    delete1=a[i];
                    delete2 = a[n-1-i];
                    break;
                }
            }
            if (delete1==-1) { pw.println("YES"); continue; }

            ArrayList<Integer> a2 = new ArrayList<Integer>();
            for (int i = 0; i <= n-1; i++) if (a[i] != delete1) a2.add(a[i]);
            ArrayList<Integer> a3 = new ArrayList<Integer>();
            for (int i = 0; i <= n-1; i++) if (a[i] != delete2) a3.add(a[i]);
            boolean works = check(a2) || check(a3);
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }

    static boolean check(ArrayList<Integer> list) {
        ArrayList<Integer> list2 = new ArrayList<Integer>();
        int size = list.size();
        for (int i = 0; i <= size-1; i++) list2.add(list.get(i));
        for (int i = 0; i <= (size-1)/2; i++) {
            if (list.get(i)!=(list.get(size-1-i))) return false;
        }
        return true;
    }
}
