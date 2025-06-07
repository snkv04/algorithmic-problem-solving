import java.util.*;
import java.io.*;

public class PhotoshootOpen2022Bronze {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        char[] cows = br.readLine().toCharArray();
        char[] gbn = new char[n/2]; // good block of 2, bad block, and neutral block
        for (int i = 0; i < n; i+=2) {
            if (cows[i]=='G'&&cows[i+1]=='G' || cows[i]=='H'&&cows[i+1]=='H') {
                gbn[i/2]='N';
            }
            if (cows[i]=='G'&&cows[i+1]=='H') {
                gbn[i/2] = 'B';
            }
            if (cows[i]=='H'&&cows[i+1]=='G') {
                gbn[i/2] = 'G';
            }
        }
        // pw.println(gbn);

        // int lastB = -1;
        // for (int i = gbn.length-1; i >= 0; i--) {
        //     if (gbn[i]=='B') {
        //         lastB = i;
        //         break;
        //     }
        // }

        // if (lastB == -1) {
        //     pw.println(0);
        //     pw.close();
        //     return;
        // }

        // TreeSet<Integer> gIndices = new TreeSet<>();
        // TreeSet<Integer> bIndices = new TreeSet<>();
        // for (int i = 0; i <= lastB; i++) {
        //     if (gbn[i]=='G') gIndices.add(i);
        //     if (gbn[i]=='B') bIndices.add(i);
        // }

        // int count = 0;
        // int last = -1;
        // if (gIndices.size()>=1) {
        //     count++;
        //     last = gIndices.pollFirst();
        //     while (!gIndices.isEmpty()) {
        //         int next = gIndices.pollFirst();
        //         if (next != last+1) count++;
        //         last = next;
        //     }
        // }
        // if (bIndices.size()>=1) {
        //     count++;
        //     last = bIndices.pollFirst();
        //     while (!bIndices.isEmpty()) {
        //         int next = bIndices.pollFirst();
        //         if (next != last+1) count++;
        //         last = next;
        //     }
        // }
        // pw.println(count);

        // compresses all of the consecutive Gs into one G, same for B, removes Ns
        // idk where i messed up the above implementation, but both solutions are
        // trying to find out the number of contiguous segments that only contain
        // either all Gs or all Bs
        ArrayList<Character> segments = new ArrayList<Character>();
        for (int i = 0; i <= n/2 - 1; i++) {
            if (gbn[i] != 'N') segments.add(gbn[i]);
        }
        for (int i = segments.size()-2; i >= 0; i--) {
            if (segments.get(i) == segments.get(i+1)) {
                segments.remove(i);
            }
        }
        pw.println(segments.get(segments.size()-1)=='G'?segments.size()-1:segments.size());

        br.close(); pw.close();

        // after looking at the sample case for a bit, i noticed that when an
        // even size prefix is flipped, 01s are changed to 10s, 10s are changed to 
        // 01s, and 11s and 00s remain unchanged (where 1s are Gs and 0s are Hs).
        // if a size 2 block is 10 (or "bad"), then flipping an even-size prefix
        // containing it may move it to a different spot but it will be good afterward.
        // the good blocks at the end do not need to be flipped. also, if a size 2 block
        // is 11 or 00, then no number of flips can ever make that block contribute to
        // a higher number of Gs in even spots. the goal is to make the final string
        // have the maximum number of G blocks. so, scanning from the right, upon seeing
        // the first bad block, we can do some flips to make things better in the prefix
        // ending at that bad block. all of the neutral blocks (11 or 00) can't change
        // the number of Gs in their right spots, so they can be effectively ignored in
        // the process of reversing prefixes. intuitively, it might seem like a good
        // idea to just count the number of bad "segments" (where a segment is a series
        // of consecutive blocks of the same type, like 101010 is made up of 10 blocks)
        // that are separated by good/neutral segments, as prefixes ending at them
        // can be reversed, but when doing this, good segments trapped between the
        // start and those will turn into bad segments. therefore, each reversal,
        // we can flip the entire prefix ending at the last bad segment, then now
        // there is a new last bad segment so we reverse the prefix ending at that, and
        // do this repeatedly until there are only good segments. therefore, although
        // the segment idea works, we have to count both the good and bad segments
        // to the left and equal to the last bad segment and not just the bad segments,
        // and that is the answer. in the implementation, instead of finding the
        // location of the last bad segment, the algorithm could instead just look
        // at all segments, and return the count of them minus one if the last segment
        // (after having completely excluded all neutral blocks/segments) was one
        // that consisted of all Gs, otherwise just return the count of segments (since
        // the last one was B blocks). this can be more easily done by compressing all
        // of the contiguous similar blocks into segments, and then finding the size
        // of the segment list. this is done in the second implementation.
    }
}
