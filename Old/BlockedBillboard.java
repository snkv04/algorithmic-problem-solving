import java.util.*;
import java.io.*;

public class BlockedBillboard {

  static int[][] graph = new int[2000][2000];
  // from -1000 to 999 both ways

  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new FileReader("billboard.in"));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("billboard.out")));

    int[] coords = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    fill(1, 1000+coords[0], 1000+coords[1], 1000+coords[2], 1000+coords[3]);
    coords = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    fill(1, 1000+coords[0], 1000+coords[1], 1000+coords[2], 1000+coords[3]);
    coords = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    fill(-1, 1000+coords[0], 1000+coords[1], 1000+coords[2], 1000+coords[3]);

    int count = 0;
    for(int i = 0; i <= 1999; i++) {
      for(int j = 0; j < 2000; j++) {
        if (graph[i][j] == 1) { count++; }
      }
    }

    pw.println(count);

    br.close(); pw.close();
  }

  static void fill (int value, int llx, int lly, int urx, int ury) {
    for (int i = llx; i <= urx-1; i++) {
      for (int j = lly; j <= ury-1; j++) {
        graph[i][j] = value;
      }
    }
  }
}
