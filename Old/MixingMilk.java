import java.io.*;

public class MixingMilk {
    public static void main(String[] args) throws FileNotFoundException, IOException{
        //read in the input
        //have two arrays: one for capacities and one for milk amounts
        //for loop 100 times to move the milk
        BufferedReader br = new BufferedReader(new FileReader("mixmilk.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("mixmilk.out")));
        int[] capacities = new int[3];
        int[] milk = new int[3];
        for(int i = 0; i <= 2; i++){
            String[] split = br.readLine().split(" ");
            capacities[i] = Integer.parseInt(split[0]);
            milk[i] = Integer.parseInt(split[1]);
        }

        for(int i = 0; i <= 99; i++) {
            int first = i % 3;
            int second = (i + 1) % 3;
            int moved = Math.min(milk[first], capacities[second] - milk[second]);
            milk[first] -= moved;
            milk[second] += moved;
        }

        for(int i = 0; i<=2; i++) pw.println(milk[i]);
        br.close(); pw.close();

    }
}
