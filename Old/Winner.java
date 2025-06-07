import java.util.*;
import java.io.*;

public class Winner {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        HashMap<String, Integer> players = new HashMap<>();
        String[] roundNames = new String[n];
        int[] roundScores = new int[n];
        for (int i = 0; i <= n-1; i++) {
            String[] line = br.readLine().split(" ");
            String name = line[0];
            int score = Integer.parseInt(line[1]);
            roundNames[i] = name;
            roundScores[i] = score;

            if (!players.containsKey(name)) {
                players.put(name, score);
            } else {
                players.put(name, players.get(name) + score);
            }
        }

        int maxScore = -1;
        for (Map.Entry<String, Integer> entry : players.entrySet()) {
            maxScore = Math.max(maxScore, entry.getValue());
        }

        HashSet<String> winners = new HashSet<>();
        for (Map.Entry<String, Integer> entry : players.entrySet()) {
            if (entry.getValue() == maxScore) winners.add(entry.getKey());
        }

        players = new HashMap<>();
        for (int i = 0; i <= n-1; i++) {
            if (players.containsKey(roundNames[i])) {
                players.put(roundNames[i], players.get(roundNames[i]) + roundScores[i]);
            } else {
                players.put(roundNames[i], roundScores[i]);
            }

            if (players.get(roundNames[i]) >= maxScore && winners.contains(roundNames[i])) {
                pw.print(roundNames[i]);
                pw.close();
                return;
            }
        }

        br.close(); pw.close();
    }
}