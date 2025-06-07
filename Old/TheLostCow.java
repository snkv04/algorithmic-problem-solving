import java.io.*;

public class TheLostCow {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader("lostcow.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("lostcow.out")));
        String[] split = br.readLine().split(" ");
        int x = Integer.parseInt(split[0]);
        int y = Integer.parseInt(split[1]);
        int currentPos = x;
        int totalDist = 0;

        //have distance variable = 1
        //while true loop
        // if y within range of currentPosition to x+dist, then add |x-y| to totalDist and break
        // else, add dist to totalDist and make currentPosition x+dist
        //double distance variable at end
        int dist = 1;
        for(;true;){
            if(y >= Math.min(x, x+dist) && y <= Math.max(x, x+dist)){
                totalDist += Math.abs(currentPos-y);
                break;
            } else {
                totalDist += Math.abs(x+dist - currentPos);
                currentPos = x+dist;
            }

            dist *= -2;
        }

        pw.print(totalDist);
        br.close(); pw.close();
    }
}
