import java.io.*;

public class FridayTheThirteenth {
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader("friday.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("friday.out")));

        int n = Integer.parseInt(br.readLine());
        int currentYear = 1899;
        // int lastYear = 1900 + n - 1;
        int numMonths = 12 * n;
        int[] counts = new int[7]; // assume it starts on december 13th, 1899
        int[] daysPerMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // counts[0]++; //adding a saturday because of the january of 1900
        int currentDay = 0;

        for(int i = 0 + 11; i <= numMonths - 1 + 11; i++) {
            // increment the year if 12 months have passed
            if ((i + 1) % 12 == 0) {
                currentYear++;
            }
            // check the year; if it's a leap year, then change the daysPerMonth array for february
            if(currentYear % 4 == 0 && !(currentYear % 100 == 0 && currentYear % 400 != 0)){
                daysPerMonth[1] = 29;
            } else {
                daysPerMonth[1] = 28;
            }

            // add the number of days from the previous month to the current day count
            currentDay += daysPerMonth[i % 12];
            
            // add to the count array depending ont he day
            counts[(currentDay % 7) - 3]++;

        }

        for(int i = 0; i<= 6; i++) {
            pw.print(counts[i] + " ");
        }
        br.close();
        pw.close();
    }
}
