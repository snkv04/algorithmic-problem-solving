import java.util.*;
import java.io.*;

public class Photoshoot2 {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        Queue<Integer> current = new LinkedList<Integer>();
        Queue<Integer> goal = new LinkedList<Integer>();
        String[] split = br.readLine().split(" ");
        for(String value: split) { current.add(Integer.parseInt(value)); }
        split = br.readLine().split(" ");
        for(String value: split) { goal.add(Integer.parseInt(value)); }
        HashSet<Integer> misplaced = new HashSet<Integer>();
        
        int count = 0;
        for(;goal.peek() != null;) {
            if(goal.peek() == current.peek()) {
                goal.poll();
                current.poll();
            } else {
                if(!misplaced.contains(current.peek())){
                    misplaced.add(goal.poll());
                    count++;
                } else {
                    misplaced.remove(current.poll());
                }
            }
        }
        pw.println(count);

        br.close(); pw.close();
    }
}
