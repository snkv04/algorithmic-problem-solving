import java.io.*;

public class WordProcessor {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new FileReader("word.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("word.out")));
        String[] line1 = br.readLine().split(" ");
        int n = Integer.parseInt(line1[0]);
        int k = Integer.parseInt(line1[1]);
        String[] words = br.readLine().split(" ");

        String[] lines = new String[n];
        int line = 0;
        for(int i = 0; i<=n-1; i++){
            //three cases:
            // the current line is null
            // the current line has words but can fit another
            // the current line has words but can't fit another
            if(lines[line] == null){
                lines[line] = words[i];
            } else {
                if(lines[line].replace(" ", "").length() + words[i].length() <= k) {
                    lines[line] += " " + words[i];
                } else {
                    line++;
                    lines[line] = words[i];
                }
            }
        }

        for(int i = 0; i <= line; i++) {
            pw.println(lines[i]);
        }

        br.close();
        pw.close();
    }
}
