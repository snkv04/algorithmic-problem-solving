import java.util.*;
import java.io.*;

// used to just be called "UdderedButNotHerd"
public class UdderedButNotHerdGold {
  public static void main(String[] args) throws Exception{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(System.out);

    String lettersHeard = br.readLine();
    
    // loop through letters in lettersHeard
    // have a taken array
    // each loop, check if the character is in the taken array
    // each time it's in the taken array, clear the taken array, add the character, and increment the count
    int count = 0;
    ArrayList<Character> taken = new ArrayList<Character>();
    for(int i = 0; i <= lettersHeard.length() - 1; i++) {
      char character = lettersHeard.charAt(i);
      if(taken.isEmpty() || taken.contains(character)){
        count++;
        taken.clear();
        taken.add(character);
      } else {
        taken.add(character);
      }
    }
    pw.print(count);
    br.close(); pw.close();
    // problem is that this doesn't account for the order of the cowphabet
  }
}