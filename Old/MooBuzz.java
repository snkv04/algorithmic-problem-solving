import java.io.*;

public class MooBuzz {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("moobuzz.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("moobuzz.out")));

        int n = Integer.parseInt(br.readLine());
        int moddedN = n % 8;
        int startingPoint = (n - moddedN) / 8 * 15;
        int count = 0;
        int value = 0;
        for(int i = startingPoint + 1; i <= startingPoint + 15; i++) {
            // checking if n is divisible by 8; only happens once
            if(n % 8 == 0) {
                value = startingPoint - 1;
                break;
            }
            
            if(count == moddedN) {
                value = i - 1;
                break;
            }
            if(i % 3 != 0 && i % 5 != 0) {
                count++;
            }
        }

        pw.println(value);

        br.close(); pw.close();
    }
}