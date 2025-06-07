import java.util.*;

public class Watermelon {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int w = sc.nextInt();
        System.out.println(w % 2 == 0 && w >= 4 ? "YES" : "NO");
    }
}
