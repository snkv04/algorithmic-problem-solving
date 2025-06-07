import java.util.*;
import java.io.*;

public class SquarePasture {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new FileReader("square.in"));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("square.out")));

    int[] coords = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    Rectangle board1 = new Rectangle(coords[0], coords[1], coords[2], coords[3]);
    coords = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    Rectangle board2 = new Rectangle(coords[0], coords[1], coords[2], coords[3]);

    int totalX = Math.max(board1.urx, board2.urx) - Math.min(board2.llx, board1.llx);
    int totalY = Math.max(board1.ury, board2.ury) - Math.min(board1.lly, board2.lly);
    int side = Math.max(totalX, totalY);
    pw.println(side * side);

    br.close(); pw.close();
  }
}

class Rectangle {
  int llx;
  int lly;
  int urx;
  int ury;

  public Rectangle (int llx, int lly, int urx, int ury) {
    this.llx = llx;
    this.lly = lly;
    this.urx = urx;
    this.ury = ury;
  }
}