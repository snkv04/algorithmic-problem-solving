import java.util.*;
import java.io.*;

public class UdderedButNotHerdBronze {
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(System.out);

    String cowphabet = br.readLine();
    String lettersHeard = br.readLine();
    
    // loop through letters in lettersHeard
    // have an endOfLast variable
    // for each letter, check if the substring of the cowphabet after the endOfLast index contains the letter
    // if it doesn't, then add to the count and start looking through a new copy of the cowphabet
    // have a taken array
    // each loop, check if the character is in the taken array
    // each time it's in the taken array, clear the taken array, add the character, and increment the count

    int count = 0;
    int endOfLast = 25;
    for(int i = 0; i <= lettersHeard.length() - 1; i++) {
      char character = lettersHeard.charAt(i);
      if(cowphabet.substring(endOfLast + 1, 26).contains(String.valueOf(character))){
        endOfLast = cowphabet.indexOf(character);
      } else {
        count++;
        endOfLast = cowphabet.indexOf(character);
      }
    }

    // int count = 1;
    // for(int i = 0; i <= lettersHeard.length() - 2; i++) {
    //   char letter = lettersHeard.charAt(i);
    //   char nextLetter = lettersHeard.charAt(i+1);
    //   if(cowphabet.indexOf(nextLetter) <= cowphabet.indexOf(letter)) {
    //     count++;
    //   }
    // }

    pw.print(count);
    br.close(); pw.close();
  }
}