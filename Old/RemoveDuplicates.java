import java.util.*;
import java.io.*;

public class RemoveDuplicates {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        ArrayList<Integer> list = new ArrayList();
        for (int i = 1; i <= n; i++) list.add(sc.nextInt());
        HashSet<Integer> used = new HashSet();
        for (int i = n-1; i >= 0; i--) {
            if (used.contains(list.get(i))) list.remove(i);
            else used.add(list.get(i));
        }
        pw.println(list.size());
        for (int element : list) pw.print(element + " ");

        sc.close(); pw.close();
    }
}
