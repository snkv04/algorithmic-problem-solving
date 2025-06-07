import java.util.*;
import java.io.*;

public class FlipTheBits {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            char[] a = br.readLine().toCharArray();
            char[] b = br.readLine().toCharArray();
            ArrayList<Integer> segments = new ArrayList<Integer>();
            int balance = 0;
            for (int i = 0; i <= n-1; i++) {
                if (a[i]=='0') {
                    balance--;
                } else {
                    balance++;
                }
                if (balance==0) segments.add(i);
            }
            // if (segments.get(segments.size()-1)!=n-1) segments.add(n-1);

            int last = -1;
            boolean works = true;
            for (int segmentEnd : segments) {
                boolean segmentWorks = true;
                boolean invert = a[last+1] != b[last+1];
                for (int i = last+2; i <= segmentEnd; i++) {
                    int numa = a[i] - '0';
                    int numb = b[i] - '0';
                    int curr = invert ? 1-numa : numa;
                    if (curr != numb) {
                        segmentWorks = false;
                        break;
                    }
                }
                if (!segmentWorks) {
                    works = false;
                    break;
                }
                last = segmentEnd;
            }
            for (int i = last+1; i <= n-1; i++) {
                int numa = a[i] - '0';
                int numb = b[i] - '0';
                if (numa != numb) {
                    works = false;
                    break;
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }
}
