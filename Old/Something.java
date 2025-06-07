import java.util.*;

public class Something {
	public static void main(String[] args) {
		PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
		pq.add(17);
		pq.add(14);
		pq.add(26);
		System.out.println(pq);
		System.out.println(pq.peek());
		pq.poll()
		;
		System.out.println(pq.peek());
		System.out.println(pq.toString())
;	}
}