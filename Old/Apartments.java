import java.util.*;

public class Apartments {
    public static void main(String[] ags){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int k = sc.nextInt();
        sc.nextLine();
        ArrayList<Integer> appList = new ArrayList<Integer>();
        for(int i = 0; i <= n-1; i++){
            appList.add(sc.nextInt());
        }
        appList.sort(null);
        System.out.println(appList);
        ArrayList<Integer> houseList = new ArrayList<Integer>();
        for(int i = 0; i <= m-1; i++){
            houseList.add(sc.nextInt());
        }
        houseList.sort(null);
        sc.close();

        // int count=0;
        // for(int i = 0;i<=n-1;i++){
        //     int x = appList.get(i);
        //     for(int j = 0;j<=houseList.size()-1;j++){
        //         int houseSize = houseList.get(j);
        //         if(Math.abs(houseSize-x) <= k){
        //             houseList.remove(j);
        //             count++;
        //             break;
        //         }
        //     }
        // }
        int count = 0;
        int i=0;
        int j=0;
        while(i <= n-1 && j <= m-1){
            if(Math.abs(appList.get(i) - houseList.get(j)) <= k){
                count++;
                i++;
                j++;
            } else {
                if (houseList.get(j) - appList.get(i) > k) {
                    i++;
                } else {
                    j++;
                }
            }
        }
        System.out.println(count);
    }
}
