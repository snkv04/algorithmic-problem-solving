import java.util.*;
import java.io.*;

public class IQTest {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        TreeSet<Integer> even = new TreeSet();
        TreeSet<Integer> odd = new TreeSet();
        for (int i = 1; i <= n; i++) {
            if (sc.nextInt()%2==0) even.add(i);
            else odd.add(i);
        }
        if (even.size()==1)pw.println(even.first());
        else pw.println(odd.first());

        sc.close(); pw.close();
    }
}
