import java.util.*;
import java.io.*;

public class AntonAndDanik {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        char[] games = br.readLine().toCharArray();
        int anton = 0, danik = 0;
        for (char game : games) {
            if (game=='A') anton++;
            else danik++;
        }
        if (anton>danik) pw.print("Anton");
        else if (anton<danik) pw.print("Danik");
        else pw.print("Friendship");

        br.close(); pw.close();
    }
}
