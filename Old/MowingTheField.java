import java.util.*;
import java.io.*;

public class MowingTheField {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader("mowing.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("mowing.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        ArrayList<MowedSquare> mowed = new ArrayList<MowedSquare>();
        MowedSquare mostRecent = new MowedSquare(0, 0, 0);
        mowed.add(mostRecent);
        int time = 0;
        for(int i = 0; i <= n-1; i++) {
            String[] split = br.readLine().split(" ");
            String direction = split[0];
            int duration = Integer.parseInt(split[1]);
            for(int j = 1; j <= duration; j++) {
                time++;
                MowedSquare newSquare = mostRecent.copy();
                newSquare.time = time;
                if (direction.equals("N")) newSquare.y++;
                else if (direction.equals("S")) newSquare.y--;
                else if (direction.equals("E")) newSquare.x++;
                else if (direction.equals("W")) newSquare.x--;
                mowed.add(newSquare);
                mostRecent = newSquare.copy();
            }
        }
        
        int maxX = Integer.MAX_VALUE;
        for(int i = 0; i < time; i++) {
            MowedSquare currentSquare = mowed.get(i);
            // pw.println("currentSquare=" + currentSquare);
            for(int j = 0; j < i; j++) {
                MowedSquare checkingSquare = mowed.get(j);
                if (checkingSquare.equals(currentSquare)){
                    if (currentSquare.time - mowed.get(j).time < maxX) {
                        maxX = currentSquare.time - mowed.get(j).time;
                    }
                    mowed.set(j, new MowedSquare(checkingSquare.x, checkingSquare.y, currentSquare.time));
                    // pw.println("found an equal: " + mowed.get(j));
                    // pw.println("maxX = " + maxX + " now breaking");
                    break;
                }
            }
        }
        if (maxX == Integer.MAX_VALUE) {
            maxX = -1;
        }
        pw.print(maxX);

        br.close(); pw.close();
    }
}

class MowedSquare {
    int x;
    int y;
    int time;
    public MowedSquare(int x, int y, int time) {
        this.x = x;
        this.y = y;
        this.time = time;
    }

    public boolean equals(MowedSquare square) {
        if(this.x == square.x && this.y == square.y) {
            return true;
        }
        return false;
    }
    
    public MowedSquare copy() {
        return new MowedSquare(this.x, this.y, this.time);
    }

    public String toString() {
        return "(" + this.x + " " + this.y + " " + this.time + ")";
    }
}