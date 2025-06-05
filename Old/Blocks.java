import java.util.*;
import java.io.*;

public class Blocks {
    
    static ArrayList<char[][]> permutations = new ArrayList<char[][]>();
    
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        char[][] blocks = new char[4][6];
        for(int i = 0; i <= 3; i++) {
            blocks[i] = br.readLine().toCharArray();
        }
        String[] words = new String[n];
        for(int i = 0; i <= n-1; i++) {
            words[i] = br.readLine();
        }

        generatePermutations(blocks, 0);
        boolean wordPossible = false;
        for(String word: words) {
            wordPossible = false;
            for(char[][] permutation: permutations) {
                if(test(permutation, word) == true) {
                    wordPossible = true;
                    break;
                }
            }

            if(wordPossible) pw.println("YES");
            else pw.println("NO");
        }

        br.close(); pw.close();
    }

    static void generatePermutations(char[][] blocks, int fixedIndex) {
        if(fixedIndex == blocks.length) {
            permutations.add(copyOf(blocks));
            return;
        } else {
            for(int i = fixedIndex; i <= blocks.length-1; i++) {
                char[] temp = Arrays.copyOf(blocks[fixedIndex], blocks[fixedIndex].length);
                blocks[fixedIndex] = Arrays.copyOf(blocks[i], blocks[i].length);
                blocks[i] = Arrays.copyOf(temp, temp.length);
                generatePermutations(blocks, fixedIndex+1);
                temp = Arrays.copyOf(blocks[fixedIndex], blocks[fixedIndex].length);
                blocks[fixedIndex] = Arrays.copyOf(blocks[i], blocks[i].length);
                blocks[i] = Arrays.copyOf(temp, temp.length);
            }
        }
    }

    // static Character[][] convert(char[][] a) {
    //     Character[][] b = new Character[a.length][a[0].length];
    //     for(int i = 0; i <= a.length-1; i++) {
    //         for(int j = 0; j <= a[0].length-1; j++) {
    //             b[i][j] = a[i][j];
    //         }
    //     }
    //     return b;
    // }

    // static String toString(char[][] permutation) {
    //     String string = "\n[";
    //     for(int i = 0; i <= permutation.length-2; i++) {
    //         string += String.valueOf(permutation[i]) + ", ";
    //     }
    //     string += String.valueOf(permutation[permutation.length-1]);
    //     string += "]\n";
    //     return string;
    // }

    static char[][] copyOf(char[][] a) {
        char[][] b = new char[a.length][a[0].length];
        for(int i = 0; i <= a.length-1; i++) {
            for(int j = 0; j <= a[0].length-1; j++) {
                b[i][j] = a[i][j];
            }
        }
        return b;
    }

    static boolean test(char[][] permutation, String word) {
        for(int i = 0; i <= permutation.length - word.length(); i++) {
            boolean works = true;
            for(int j = 0; j <= word.length() - 1; j++) {
                if(!in(permutation[i+j], word.charAt(j))) {
                    works = false;
                }
            }
            if(works) return true;
        }
        return false;
    }

    static boolean in(char[] block, char letter) {
        for(char side: block) {
            if(letter == side) return true;
        }
        return false;
    }
}
