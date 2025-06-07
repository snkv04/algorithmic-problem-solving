import java.util.*;
import java.io.*;

public class RanomNumbers {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        HashMap<Character, Integer> map = new HashMap<Character, Integer>();
        map.put('A', 0);
        map.put('B', 1);
        map.put('C', 2);
        map.put('D', 3);
        map.put('E', 4);
        HashMap<Integer, Integer> map2 = new HashMap<Integer, Integer>();
        map2.put(0, 1);
        map2.put(1, 10);
        map2.put(2, 100);
        map2.put(3, 1000);
        map2.put(4, 10000);
        while (t-->0) {
            String[] line = br.readLine().split("");
            int[] mapped = new int[line.length+1];
            for (int i = 1; i <= line.length; i++) {
                mapped[i] = map.get(line[line.length-i].charAt(0));
            }
            // pw.println(Arrays.toString(mapped));

            long[][][] memo = new long[line.length+1][2][5];
            for (int i = 1; i <= line.length; i++) {
                for (int j=0; j<=1; j++) for (int k = 0; k <= 4; k++) memo[i][j][k] = (long) -2e10;

                // choose not to change
                int currChar = mapped[i];
                // memo[i][0][Math.max(currChar, mapped[i-1])] = Math.max(memo[i][0][Math.max(currChar, mapped[i-1])],
                //     memo[i-1][0][mapped[i-1]] + map2.get(currChar) * (currChar >= mapped[i-1] ? 1 : -1));
                for (int j = 0; j <= 4; j++) {
                    memo[i][0][Math.max(currChar, j)] = Math.max(memo[i][0][Math.max(currChar, j)],
                        memo[i-1][0][j] + map2.get(currChar) * (currChar >= j ? 1 : -1));
                }


                // choose not to change, but there was a change already
                for (int j = 0; j <= 4; j++) {
                    memo[i][1][Math.max(currChar, j)] = Math.max(memo[i][1][Math.max(currChar, j)],
                        memo[i-1][1][j] + map2.get(currChar) * (currChar >= j ? 1 : -1));
                }

                // choose to change this character
                for (int j = 0; j <= 4; j++) {
                    for (int k = 0; k <= 4; k++) {
                        if (k != currChar)
                            memo[i][1][Math.max(j, k)] = Math.max(memo[i][1][Math.max(j, k)],
                                memo[i-1][0][j] + map2.get(k) * (k >= j ? 1 : -1));
                    }
                }

                // for (int index = 0; index <= line.length; index++) {
                //     pw.print("i = "+index+" | ");
                //     for (int changed = 0; changed <= 1; changed ++) 
                //         pw.print(Arrays.toString(memo[index][changed]) + " ");
                //     pw.println();
                // }
                // pw.println();
            }

            long ans = (long) -2e10;
            for (int changed = 0; changed <= 1; changed++) {
                for (int maxSeenSoFar = 0; maxSeenSoFar <= 4; maxSeenSoFar ++) {
                    ans = Math.max(ans, memo[line.length][changed][maxSeenSoFar]);
                }
            }
            pw.println(ans);
        }

        br.close(); pw.close();

        // basically, we want to pick one element to change to one specific value
        // so that the sum of the string is at maximum. obviously, the brute force
        // solution would be to try changing every element to every value, and for
        // each of the 5n possibilities, check the string; however, this would be
        // on the order of an O(n^2) time complexity, and since the string length
        // can be 200,000, this is too slow. using dynamic programming, we can check
        // the best possible choice at each index, making sure to only make at most
        // one change overall. first, the string can be reversed so that instead of
        // having letters depend on the letters to the right, they only depend
        // on the letters to the left. now, after padding the original string with
        // a buffer value on the left (which is 0 for A, since this won't affect
        // anything at all) in order to make indexing easier and clearner, we can
        // have memo[i][j][k] be the maximum sum so far at index i, assuming that
        // there have been j changes so far and the maximum value to the left
        // (including the value at index i) is k. for each element, we can either
        // leave it as is and have no changes before it either, we can not change
        // it but have a change occur at some point prior (meaning j must equal 1),
        // or iterate upon the 5 choices for the current element.
        // if we do nothing and nothing has happened, then first of all we would
        // be filling in a spot in the memo array where j equals 0. for this, we
        // can look at all of the different changes=0 elements in the memo array
        // for the previous index (i-1) and not change the current element, meaning
        // that for the memo array element described by index=i, changes=0,
        // maxLetterSoFar=Math.max(currentLetter, previousIndex'sLetter), we either
        // add or subtract the current letter (again, doing this for each of the 5
        // changes=0 elements at index i-1). two things. first, the reason why we
        // have to update only the element indexed by the maximum of either the
        // current letter or the past letter (and not just the element indexed by
        // the current letter) is because the current letter could be less than
        // something before it, and it would be incorrect to say that the maxSoFar
        // letter is the current one (because that could instead be set to whatever
        // it already was). second: the reason why we have to iterate over all the
        // changes=0 elements at the previous index instead of just looking at the
        // changes=0 element indexed by the previous character in the string is that
        // the maxSoFar value could indeed be defined by a character a while ago
        // and not simply the most recent letter before the current letter, so it
        // is instead correct to look at all possibilities; since at each index
        // we don't just memoize the result and say that the maxSoFar value is
        // the current character but actually max it (which is logically correct),
        // the memoized result may not be located at maxSoFar=lastLetter but we
        // will still find it by looking at all choices.
        // now, the second choice would be to not change the current character,
        // but to also consider that a previous character was changed. even though
        // we aren't changing the current character, we still have that changed=1
        // because it has happened at some time point before or equal to now. for
        // this, we consider the current character as it is, look over all the
        // possibilities for the previous index's changed=1 values, either add
        // or subtract the current letter's value, and then take the max over all
        // of these 5 values.
        // lastly, we can iterate over the possibilities of changing the current
        // character. for this choice, we have to assume that nothing has been
        // changed in the past. so, for each choice for the current character (except
        // that which equals the actual current letter, because that choice has
        // ALREADY BEEN CONSIDERED), we look over all of the memoized results such
        // that index=i-1, changed=0. this makes us search through 20 (4*5) different
        // possibilities, and take the max of all of them. to be clear, for each
        // choice, we either add or subtract the current choice of letter depending
        // on what is appropriate.
        // at the end, we look at every possible value corresponding to the last
        // index; these are the 5 choices for each of changed=0 and changed=1,
        // although of course only one of the changed=0 will be a clear maximum
        // (since only one maxSoFar value can be true assuming that nothing was
        // changed from the original string) but we still have to check all of those
        // 5 since the last letter might not have been the max so far. after looking
        // at these 10 values, we take the max of them and return.
    }
}

// import java.util.*;
// import java.io.*;

// public class RanomNumbers {
//     public static void main(String[] args) throws Exception {
//         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//         PrintWriter pw = new PrintWriter(System.out);

//         int t = Integer.parseInt(br.readLine());
//         for (int i=1; i<=t; i++) {
//             char[] digits = br.readLine().toCharArray();
//             int[] values = convert(digits);
//             int[] signs = new int[values.length];

//             int max = values[values.length-1];
//             signs[signs.length-1] = 1;
//             int numPositive = 1;
//             for (int j = values.length - 2; j >= 0; j--) {
//                 if (values[j] >= max) {
//                     signs[j] = 1;
//                     max = values[j];
//                     numPositive++;
//                 } else signs[j] = -1;
//             }
//             // pw.println(Arrays.toString(values));
//             // pw.println(Arrays.toString(signs));

//             if (numPositive == values.length) {
//                 values[0] = 10000;
//             } else {
//                 int largest = Integer.MIN_VALUE;
//                 for (int j = 0; j <= values.length-1; j++) {
//                     // if (signs[j] == -1) {
//                         largest = Math.max(largest, values[j]);
//                     // }
//                 }

//                 // now pass through the array and for the first value encountered equal to
//                 // the largest negative value, set it to E and then exit
//                 for (int j = 0; j <= values.length-1; j++) {
//                     if (values[j] == largest) {
//                         values[j] = 10000;
//                         signs[j] = 1;
//                         break;
//                     }
//                 }
//             }
//             // pw.println(Arrays.toString(values));
//             // pw.println(Arrays.toString(signs));

//             long sum = 0;
//             for (int j = 0; j <= values.length-1; j++) {
//                 sum += (long) values[j] * signs[j];
//             }
//             pw.println(sum);
//         }

//         br.close(); pw.close();
//     }

//     static int[] convert(char[] digits) {
//         int[] values = new int[digits.length];
//         for (int i = 0; i <= digits.length-1; i++) {
//             if (digits[i] == 'A') values[i] = 1;
//             if (digits[i] == 'B') values[i] = 10;
//             if (digits[i] == 'C') values[i] = 100;
//             if (digits[i] == 'D') values[i] = 1000;
//             if (digits[i] == 'E') values[i] = 10000;
//         }
//         return values;
//     }
// }
