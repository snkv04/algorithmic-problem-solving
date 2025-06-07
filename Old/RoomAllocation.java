import java.util.*;
import java.util.concurrent.*;

public class RoomAllocation {
    public static void main(String[] args) throws InterruptedException{
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
        pq.add(1);System.out.println(pq);
        pq.add(7);System.out.println(pq);
        pq.add(17);System.out.println(pq);
        pq.add(101);System.out.println(pq);
        pq.add(51);System.out.println(pq);
        pq.add(74);System.out.println(pq);
        pq.add(32);System.out.println(pq);
        pq.add(24);System.out.println(pq);
        pq.add(24);System.out.println(pq);
        pq.add(24);System.out.println(pq);
        pq.add(0);pq.add(0);pq.add(0);pq.add(0);pq.add(0);pq.add(0);
        pq.add(0);pq.add(0);pq.add(0);pq.add(0);pq.add(0);pq.add(0);
        pq.add(0);pq.add(0);pq.add(0);pq.add(0);pq.add(0);pq.add(0);
        TimeUnit.SECONDS.sleep(5);
        System.out.println(pq);
        for(int i = 1;i<=28;i++){
            System.out.println(pq.poll());
        }
    }
}
