import java.util.*;
import java.io.*;

public class MilkMeasurement {
    static String[] cowNames = {"Bessie", "Elsie", "Mildred"};
    public static void main(String[] args) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader("measurement.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("measurement.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        String[] notes = new String[n];
        for(int i = 0; i <= n-1; i++) {
            notes[i] = br.readLine();
        }
        Arrays.sort(notes, new MyComp());

        // int[] days = new int[n];
        String[] names = new String[n];
        int[] changes = new int[n];
        for(int i = 0; i <= n-1; i++) {
            String[] splitUp = notes[i].split(" ");
            // days[i] = Integer.parseInt(splitUp[0]);
            names[i] = splitUp[1];
            changes[i] = Integer.parseInt(splitUp[2]);
        }

        int[] cowOutputs = new int[3]; // Bessie, Elsie, and Mildred
        for(int i = 0; i <= 2; i++) {cowOutputs[i] = 7;}

        //for loop going through each note
        //for each note, change the output of the corresponding cow
        //then, find the max output cows and see if it changed
        //if it did, then update a counter
        int count = 0;
        ArrayList<String> maxArray = makeMaxArray(cowOutputs);
        for(int i = 0; i<= n-1; i++) {
            if(names[i].equals("Bessie")){
                cowOutputs[0] += changes[i];
            } else if (names[i].equals("Elsie")) {
                cowOutputs[1] += changes[i];
            } else {
                cowOutputs[2] += changes[i];
            }

            if (!(makeMaxArray(cowOutputs).equals(maxArray))){
                count++;
                maxArray = makeMaxArray(cowOutputs);
            }
        }

        pw.println(count);

        br.close();
        pw.close();
    }

    public static ArrayList<String> makeMaxArray(int[] outputs) {
        int max = -1;
        ArrayList<String> maxArray = new ArrayList<String>(3);
        for(int i = 0; i<=2; i++) {
            if(outputs[i] > max){ // if the output is greater than the max output
                max = outputs[i]; // change the max output
                maxArray.clear(); maxArray.add(cowNames[i]); // clear the maxArray and add the new max cow
            } else if (outputs[i] == max) { // if the output is equal to the max
                maxArray.add(cowNames[i]); //add the current cow to maxArray
            }
        }
        return maxArray;
    }
}

class MyComp implements Comparator<String>{
    public int compare(String s1, String s2) {
        // if(Integer.parseInt(s1.split(" ")[0]) < Integer.parseInt(s2.split(" ")[0])) {
        //     return -1;
        // } else if (Integer.parseInt(s1.split(" ")[0]) == Integer.parseInt(s2.split(" ")[0])) {
        //     return 0;
        // } else {
        //     return 1;
        // }
        return Integer.compare(Integer.parseInt(s1.split(" ")[0]), Integer.parseInt(s2.split(" ")[0]));
    }
}