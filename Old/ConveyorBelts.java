import java.util.*;

public class ConveyorBelts {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for (int i = 1; i <= t; i++) {
            int n = sc.nextInt();
            int x1 = sc.nextInt();
            int y1 = sc.nextInt();
            int x2 = sc.nextInt();
            int y2 = sc.nextInt();
            // double center = ((double) n) / 2 + 0.5;
            int layer1 = Math.min(x1, Math.min(y1, Math.min(n+1-x1, n+1-y1)));
            int layer2 = Math.min(x2, Math.min(y2, Math.min(n+1-x2, n+1-y2)));
            System.out.println(Math.abs(layer1 - layer2));
        }
    }
}
