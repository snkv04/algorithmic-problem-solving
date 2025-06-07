import java.util.*; import java.io.*;

public class HoofPaperScissorsBrozne {
    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("hps.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("hps.out")));

        int n = Integer.parseInt(br.readLine());
        int[] cow1 = new int[n];
        int[] cow2 = new int[n];
        for (int i = 0; i <= n-1; i++) {
            String[] line = br.readLine().split(" ");
            cow1[i] = Integer.parseInt(line[0]);
            cow2[i] = Integer.parseInt(line[1]);
        }

        int countIf1 = 0, countIf2 = 0;
        for (int i = 0; i <= n-1; i++) {
            countIf1 += gameV1(cow1[i], cow2[i]);
            countIf2 += gameV2(cow1[i], cow2[i]);
        }
        pw.print(Math.max(countIf1, countIf2));

        br.close(); pw.close();
    }

    static int gameV1(int cow1, int cow2) {
        if ((cow1==3&&cow2==2) || (cow1==2&&cow2==1) || (cow1==1&&cow2==3)) {
            return 1;
        } else return 0;
    }

    static int gameV2(int cow1, int cow2) {
        if ((cow1==3&&cow2==1) || (cow1==1&&cow2==2) || (cow1==2&&cow2==3)) {
            return 1;
        } else return 0;
    }
}
