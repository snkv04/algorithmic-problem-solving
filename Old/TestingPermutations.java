import java.util.*;

public class TestingPermutations {
    public static void main(String[] args) {
        generatePermutations(new int[]{1,2,3,4}, 0);
    }

    static int firstBlock = 0;
    static int secondBlock = 0;
    static void generatePermutations(int[] a, int fixedIndex) {
        
        if(fixedIndex == a.length) {
            firstBlock++;
            System.out.println("firstBlock."+firstBlock+" = " + Arrays.toString(a));
            return;
        } else {
            for(int i = fixedIndex; i <= a.length-1; i++) {
                
                int temp = a[fixedIndex];
                a[fixedIndex] = a[i];
                a[i] = temp;
                // secondBlock++;
                // System.out.println("secondBlock."+secondBlock+" after swap = " + Arrays.toString(a));
                generatePermutations(a, fixedIndex+1);
                temp = a[fixedIndex];
                a[fixedIndex] = a[i];
                a[i] = temp;
                // System.out.println("secondBlock."+secondBlock+" after second swap = " + Arrays.toString(a));
            }
        }
    }
}
