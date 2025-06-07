import java.util.*;
import java.io.*;

public class RGBSubstring {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        // int queries = Integer.parseInt(br.readLine());
        // for (int q = 1; q <= queries; q++) {
        //     String[] line = br.readLine().split(" ");
        //     int n = Integer.parseInt(line[0]);
        //     int k = Integer.parseInt(line[1]);
        //     char[] s = br.readLine().toCharArray();

        //     // looking at a k-long window that STARTS with either R, G, or B
        //     char[] RGB = {'R', 'G', 'B'};
        //     char[] R = new char[k];
        //     char[] G = new char[k];
        //     char[] B = new char[k];
        //     for (int i = 0; i <= k-1; i++) {
        //         R[i] = RGB[i%3];
        //         G[i] = RGB[(i+1)%3];
        //         B[i] = RGB[(i+2)%3];
        //     }
        //     // pw.println(R);
        //     // pw.println(G);
        //     // pw.println(B);

        //     int[][] memo = new int[n-k+1][3];
        //     int min = Integer.MAX_VALUE;
        //     // now filling in the vals for the last substring, after which it's much
        //     // more efficient
        //     int numForR=0, numForG=0, numForB=0;
        //     for (int i = n-k; i <= n-1; i++) {
        //         if (s[i] != R[i-(n-k)]) {
        //             numForR++;
        //         }
        //         if (s[i] != G[i-(n-k)]) {
        //             numForG++;
        //         }
        //         if (s[i] != B[i-(n-k)]) {
        //             numForB++;
        //         }
        //     }
        //     // pw.println(numForR+" "+numForG+" "+numForB);
        //     memo[n-k][0]=numForR;
        //     memo[n-k][1]=numForG;
        //     memo[n-k][2]=numForB;
        //     min = Math.min(Math.min(min, numForR), Math.min(numForG, numForB));

        //     // now changes the counts for each subarray, assuming that the subarray began
        //     // at either R (0), G (1), or B (2)
        //     for (int i = n-k-1; i >= 0; i--) {
        //         // have to add changes depending on if the new starting character
        //         // fits in or not
        //         memo[i][0] = memo[i+1][1] + (s[i]=='R'?0:1);
        //         memo[i][1] = memo[i+1][2] + (s[i]=='G'?0:1);
        //         memo[i][2] = memo[i+1][0] + (s[i]=='B'?0:1);

        //         // have to remove changes depending on if the ending character which was removed
        //         // fits in or not
        //         memo[i][0] -= (s[i+k]==G[k-1]?0:1);
        //         memo[i][1] -= (s[i+k]==B[k-1]?0:1);
        //         memo[i][2] -= (s[i+k]==R[k-1]?0:1);
        //         min = Math.min(Math.min(min, memo[i][0]), Math.min(memo[i][1], memo[i][2]));
        //     }
        //     pw.println(min);
        // }

        // br.close(); pw.close();

        // LET'S GOOO
        // basically, we want to look at every single k-long subarray of the n-sized string
        // and see the minimum characters we have to remove for it to be a substring of
        // RGBRGBRGB... . it is evident (and a very important observation) that no matter what,
        // if the correct number of changes are made, then the k-long substring that we
        // choose will either look like RGBRGB..., GBRGBRGB..., or BRGBRGB... for a length
        // of k. we can start by looking at the k-long substring at the very end, and see
        // how many characters we would need to change if we assumed that it started with
        // R, started with G, or started with B. for this single substring, we have to
        // look at every character in this last substring. now, we can move left. for each
        // step left, we want to use the previous results (from the substring that was 1
        // to the right). let's first assume that the current step's substring starts with R.
        // we take the num of changes for G from the previous step and set the changes for R
        // for the current step to that, and if the new character we are adding to the start
        // is an R, then we don't add anything to the num of changes, otherwise we have to
        // since it would have to be changed to an R as we assume the substring starts with
        // an R. now, for the character that was at the end of the previous step that is
        // no longer at the end of the current step: if it fit in with the end of the
        // k-long G string, then we don't decrement the changes for the current step as
        // that was already good and didn't need any changes; otherwise, we do decrement
        // the changes for the current step, since we no longer need to edit that character.
        // we do this same process, looking at the start and end of each window, for the
        // assumption that each current step's substring starts with G and then with B.
        // also, the reason why for the current step we don't look at the previous step's
        // result for the same character but rather for the character right after (like
        // looking at the result for G from window [4,7] to find R's result for [3,6])
        // is because the substring for that character from the previous step would
        // perfectly overlay the substring from the current step and the current step's
        // character, other than the first and last characters which we look at, if all
        // the changes we count were actually made. so, we can count the changes this way.
        // then, we take the minimum from the entire array of memoized results, across
        // all k-long subarrays and all assumptions for what the subarray starts with,
        // and that is the answer.
        // apparently another way to do it was to instead generate 3 n-long arrays, each
        // starting with R, G, or B, and then use those to calculate the changes for each
        // subarray. this would still require looking at the results for the offset character
        // and not the same current character, though (i think). but it requires less
        // mental math gymnastics to think about the indices, lol.
        // in addition, another optimization would be to generate 3 arrays of 1s and 0s
        // (or booleans). for the first, we can set an index's value to 0 if the element
        // of s aligns with the same index's element of the n-long R-string, and 1 otherwise.
        // same thing with the n-long B and G arrays. then we can just do a sliding
        // k-long window for all 3, counting the minimum k-long subarray sum across all
        // 3 options, which is still O(n). since we want the min number of changes,
        // this way we just set arrays which represent the changes for each element, one
        // array for each of the 3 assumptions. the sliding window operation is where we
        // can take care of the minimum part of the problem. the whole offset thing is
        // taken care of too, because for each of the 3 choices for every susbtring, it
        // is present within one of the R, G, or B arrays anyway. implementation is below.

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int queries = Integer.parseInt(br.readLine());
        for (int q = 1; q <= queries; q++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            char[]s = br.readLine().toCharArray();

            char[] RGB = {'R', 'G', 'B'};
            char[] R = new char[n];
            char[] G = new char[n];
            char[] B = new char[n];
            for (int i = 0; i <= n-1; i++) {
                R[i] = RGB[i%3];
                G[i] = RGB[(i+1)%3];
                B[i] = RGB[(i+2)%3];
            }

            int[][] changes = new int[n][3];
            for (int i = 0; i <= n-1; i++) {
                changes[i][0] = (R[i]==s[i])?0:1;
                changes[i][1] = (G[i]==s[i])?0:1;
                changes[i][2] = (B[i]==s[i])?0:1;
            }

            int min = Integer.MAX_VALUE;
            for (int i = 0; i <= 2; i++) {
                // the first step is the window from 0 to k-1
                int curr = 0;
                for (int j = 0; j <= k-1; j++) {
                    curr += changes[j][i];
                }
                min = Math.min(curr, min);

                // the remaining steps are each aken care of in O(1), going from k to n-1
                for (int j = 1; j <= n-k; j++) {
                    curr -= changes[j-1][i];
                    curr += changes[j+k-1][i];
                    min = Math.min(curr, min);
                }
            }
            pw.println(min);
        }

        br.close(); pw.close();
    }
}
