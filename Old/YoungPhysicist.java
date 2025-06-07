import java.util.*;
import java.io.*;

public class YoungPhysicist {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int x=0, y=0, z=0;
        for (int i = 0; i <= n-1; i++) {
            x+=sc.nextInt();
            y+=sc.nextInt();
            z+=sc.nextInt();
        }
        pw.println(x==0&&y==0&&z==0?"YES":"NO");

        sc.close(); pw.close();
    }
}
