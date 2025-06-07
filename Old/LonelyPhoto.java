import java.io.*;

public class LonelyPhoto {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        String line = br.readLine();
        char[] lineArray = line.toCharArray();
        
        // have i go through the indices 0 to n-3
        // for each i, have another for loop that changes the length of each window from 3 to n-i
        // count the Gs and Hs in the first substring
        // if throwaway, increment throwaway
        // as the length of the window increases, increment gCount or hCount depending on the letter
        // check if the counts of the subarray indicate a throwaway photo
        // if gCount and hCount are ever both above 1, ignore the rest of the subarrays for
        // index i and just move to the next index
        int throwOut = 0;
        for(int i = 0; i <= n-3; i++) {
            int gCount = 0;
            int hCount = 0;
            for(int j = i; j < i + 2; j++) {
                if(lineArray[j] == 'G') gCount++;
                else hCount++; 
            }

            for(int j = 3; j <= n-i; j++) {
                if(lineArray[i+j-1] == 'G') gCount++;
                else hCount++;

                if(gCount == 1 || hCount == 1) throwOut++; // checking if lonely

                if(gCount > 1 && hCount > 1) break; // no more windows starting at i will be lonely
            }
        }

        pw.println(throwOut);

        br.close(); pw.close();
    }
}
