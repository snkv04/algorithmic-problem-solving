import java.io.*;

public class Herdle {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // let a simple 1D array represent the 3x3 grid, with the array having a length of 9
        // for each cow in the actual grid, check if the cow in the same spot in the guess grid is the same
        // if so, increment a green counter and then change that cow to some random non alphabet character
        // then, after checking all greens, for each cow in the answer grid, check if the letter is found
        // in the guess grid
        // all of the green cows should already be changed so they won't be counted twice
        // if that letter is found, then increment a yellow counter and change that cow in the guess grid
        // to a random character
        String actualGrid = "", guessGrid = "";
        for(int i = 1; i <=3; i++) {
            actualGrid += br.readLine();
        }
        for(int i = 1; i <=3; i++) {
            guessGrid += br.readLine();
        }
        char[] actualGridArray = actualGrid.toCharArray();
        char[] guessGridArray = guessGrid.toCharArray();

        int greenCount = 0, yellowCount = 0;
        for(int i = 0; i <= 8; i++) {
            if(actualGridArray[i] == guessGridArray[i]) {
                greenCount++;
                guessGridArray[i] = '.';
                actualGridArray[i] = ';';
            }
        }
        for(int i = 0; i <= 8; i++) {
            char cow = actualGridArray[i];
            for(int j = 0; j <= 8; j++) {
                if(guessGridArray[j] == cow) {
                    yellowCount++;
                    guessGridArray[j] = '.';
                    break;
                }
            }
        }
        pw.println(greenCount);
        pw.println(yellowCount);

        br.close(); pw.close();
    }
}