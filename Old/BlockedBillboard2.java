import java.util.*;
import java.io.*;

public class BlockedBillboard2 {
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new FileReader("billboard.in"));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("buffered.out")));

    

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