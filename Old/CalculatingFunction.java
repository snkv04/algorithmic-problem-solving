import java.util.*;
import java.io.*;

public class CalculatingFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        long n = Long.parseLong(br.readLine());
        if (n%2==0) pw.print(n/2);
        else pw.print(-(n/2)-1);

        br.close(); pw.close();
    }
}
