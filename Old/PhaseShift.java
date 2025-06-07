import java.util.*;
import java.io.*;

public class PhaseShift {
    static char[] alphabet = "abcdefghijklmnopqrstuvwxyz".toCharArray();
    static int[] parent;
    static int[] size;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int tests = Integer.parseInt(br.readLine());
        for (int i = 1; i <= tests; i++) {
            int n = Integer.parseInt(br.readLine());
            char[] t = br.readLine().toCharArray();
            int[] tNums = convert(t);
            int[] incoming = new int[26];
            int[] outgoing = new int[26];
            parent = new int[26];
            size = new int[26];
            for (int j = 0; j <= 25; j++) {
                incoming[j] = -1;
                outgoing[j] = -1;
                parent[j] = j;
                size[j] = 1;
            }

            int[] sNums = new int[n];
            for (int j = 0; j <= n-1; j++) {
                // tnums[j] is character we're finding something for
                if (incoming[tNums[j]] != -1) {
                    sNums[j] = incoming[tNums[j]];
                    continue;
                } else {
                    // now selecting a character for s[j]
                    for (int k = 0; k <= 25; k++) { // each k is a character
                        if ((find(k) == find(tNums[j]) && size[k] != 26) || outgoing[k] != -1) {
                            continue;
                        } else {
                            incoming[tNums[j]] = k;
                            outgoing[k] = tNums[j];
                            union(k, tNums[j]);
                            sNums[j] = k;
                            break;
                        }
                    }
                }
            }
            // pw.println("incoming="+Arrays.toString(incoming));
            // pw.println("outgoing="+Arrays.toString(outgoing));

            char[] s = new char[n];
            for (int j = 0; j <= n-1; j++) { s[j] = alphabet[sNums[j]]; }
            pw.println(s);
        }

        br.close(); pw.close();
    }

    static int find(int x) {
        if (parent[x] == x) return x;
        else {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    static void union(int a, int b) {
        int c = find(a);
        int d = find(b);
        if (c!=d) {
            parent[d] = c;
            int sum = size[c] + size[d];
            size[c] = sum;
            size[d] = sum;
            size[a] = sum;
            size[b] = sum;
        }
    }

    static int[] convert(char[] tString) {
        // a=0, b=1, etc.
        HashMap<Character, Integer> alphabet = new HashMap<Character, Integer>();
        alphabet.put('a',0);
        alphabet.put('b',1);
        alphabet.put('c',2);
        alphabet.put('d',3);
        alphabet.put('e',4);
        alphabet.put('f',5);
        alphabet.put('g',6);
        alphabet.put('h',7);
        alphabet.put('i',8);
        alphabet.put('j',9);
        alphabet.put('k',10);
        alphabet.put('l',11);
        alphabet.put('m',12);
        alphabet.put('n',13);
        alphabet.put('o',14);
        alphabet.put('p',15);
        alphabet.put('q',16);
        alphabet.put('r',17);
        alphabet.put('s',18);
        alphabet.put('t',19);
        alphabet.put('u',20);
        alphabet.put('v',21);
        alphabet.put('w',22);
        alphabet.put('x',23);
        alphabet.put('y',24);
        alphabet.put('z',25);
        int[] result = new int[tString.length];
        for (int i =0; i <= tString.length-1; i++) {
            result[i] = alphabet.get(tString[i]);
        }
        return result;
    }
}
