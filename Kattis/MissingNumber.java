import java.util.*;
import java.io.*;

public class MissingNumber {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int[] a = Arrays.stream(br.readLine().split("")).mapToInt(Integer::parseInt).toArray();
        int n = a.length;
        // pw.println(Arrays.toString(a));
        // pw.println(toNum(a));
        // pw.println(Arrays.toString(toArray(toNum(a))));

        TreeSet<Integer> possible = new TreeSet<>();
        for (int lenFirst = 1; lenFirst <= 5; lenFirst++) {
            if ((lenFirst) > a.length) break;

            int firstNum = 0, multiplier = 1;
            for (int i = lenFirst-1; i >= 0; i--) {
                firstNum += a[i] * multiplier;
                multiplier *= 10;
            }

            int last = firstNum;
            ArrayList<Integer> nums = new ArrayList<>();
            boolean valid = true;
            nums.add(last);
            for (int i = lenFirst; i <= n-1; ) {
                int c = last+1, d = last + 2;
                int len1 = String.valueOf(c).length(), len2 = String.valueOf(d).length();
                boolean good1 = false, good2 = false;
                if (i + len1 <= n) {
                    int[] arr = toArray(c);
                    boolean works = true;
                    for (int j = 0; j <= len1-1; j++) {
                        // pw.println("j="+j+", arr[j]="+arr[j]+", a[i+j]="+a[i+j]);
                        if (arr[j] != a[i+j]) {
                            works = false;
                            break;
                        }
                    }
                    if (works) good1 = true;
                }
                if (i + len2 <= n) {
                    int[] arr = toArray(d);
                    boolean works = true;
                    for (int j = 0; j <= len2-1; j++) {
                        if (arr[j] != a[i+j]) {
                            works = false;
                            break;
                        }
                    }
                    if (works) good2 = true;
                }
                // pw.println("last="+last+", c="+c+", good1="+good1+", d="+d+", good2="+good2+", i="+i);

                if (!good1 && !good2) {
                    valid = false;
                    break;
                } else if (good1 && good2) {
                    // tjis case cannot happen
                    pw.println("??????");
                } else if (good1) {
                    i += String.valueOf(c).length();
                    last = c;
                    nums.add(last);
                } else {
                    i += String.valueOf(d).length();
                    last = d;
                    nums.add(last);
                }
                // pw.println();
            }
            // pw.println("nums = " + nums);
            
            if (!valid) continue;
            ArrayList<Integer> skipped = new ArrayList<Integer>();
            for (int i = 1; i <= nums.size()-1; i++) {
                if (nums.get(i) != nums.get(i-1)+1) {
                    skipped.add(nums.get(i)-1);
                }
            }
            if (skipped.size() == 0) {
                possible.add(nums.get(0)-1);
                possible.add(nums.get(nums.size()-1)+1);
            } else if (skipped.size() == 1) {
                possible.add(skipped.get(0));
            }
        }
        if (possible.contains(0)) possible.remove(0);
        if (possible.contains(100000)) possible.remove(100000);
        pw.println(possible.size());
        for (int num : possible) pw.print(num+" ");
        pw.println();
    }

    static int[] toArray(int num) {
        int len = String.valueOf(num).length();
        int[] result = new int[String.valueOf(num).length()];
        for (int i = len-1; i >= 0; i--) {
            result[i] = num % 10;
            num /= 10;
        }
        return result;
    }

    static int toNum(int[] arr) {
        int num = 0;
        int multiplier = 1;
        for (int i = arr.length-1; i >= 0; i--) {
            num += arr[i] * multiplier;
            multiplier *= 10;
        }
        return num;
    }
}
