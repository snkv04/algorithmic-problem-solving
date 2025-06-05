import java.util.*;
import java.io.*;

public class ConcertTickets {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        int[] ticketsArray = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        TreeMap<Integer, Integer> tickets = new TreeMap<Integer, Integer>();
        for(int i = 0; i<=n-1; i++){
            int ticketPrice = ticketsArray[i];
            if (tickets.containsKey(ticketPrice)) tickets.put(ticketPrice, tickets.get(ticketPrice) + 1);
            else tickets.put(ticketPrice, 1);
        }

        int[] customers = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        // Queue<Integer> cList = new LinkedList<Integer>();
        // for(int i=0;i<=m-1;i++){
        //     cList.add(Integer.parseInt(st.nextToken()));
        // }
        for (int i = 0; i <= m-1; i++) {
            int customerPrice = customers[i];
            if (tickets.size() == 0 || customerPrice < tickets.firstKey()) pw.println(-1);
            else {
                int selectedTicket = tickets.floorKey(customerPrice);
                pw.println(selectedTicket);
                // now removes the ticket paid for
                tickets.put(selectedTicket, tickets.get(selectedTicket) - 1);
                if (tickets.get(selectedTicket) == 0) {
                    tickets.remove(selectedTicket);
                }
            }
        }
        br.close();
        pw.close();

        // for(int i=0; i<=m-1; i++){
            
        //     if(tickets.isEmpty() || cList.peek() < tickets.get(0)){
        //         System.out.println(-1);
        //         cList.poll();
        //     } else {
        //         int c = cList.peek();
        //         for(int j = tickets.size()-1;j>=0;j--){
        //             if(tickets.get(j)<=c){
        //                 System.out.println(tickets.get(j));
        //                 tickets.remove(j);
        //                 cList.poll();
        //                 break;
        //             }
        //         }
        //     }
        // }
    }
}
