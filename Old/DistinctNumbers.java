import java.util.*;

public class DistinctNumbers {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        sc.nextLine();
        String[] numList = sc.nextLine().split(" ");
        HashSet<Integer> hs = new HashSet<Integer>();
        for(int i = 0; i <= numList.length - 1; i++) {
            hs.add(Integer.parseInt(numList[i]));
        }
        System.out.println(hs.size());
        sc.close();
    }
}
