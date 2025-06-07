import java.util.*;
import java.io.*;

public class ForeignFootball {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);
        
        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    public static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        // String[][] input = new String[n][n];
        // for (int i = 0; i < n; i++) {
        //     input[i] = br.readLine().split(" ");
        // }
        String[][] input = new String[2][2];
        input[0][0] = "*"; input[1][1] = "*";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i <= 2; i++) {
            for (int j = 1; j <= 33332; j++) {
                sb.append("a");
            }
            sb.append("b");
        }
        input[0][1] = sb.toString();
        input[1][0] = sb.toString();

        /*
         * go through the first row. for all possible prefixes, the rest of each string are the other team names.
         *      gather all the team names, and then go through all other cells in the table. if they match with
         *      the expected concatenation, then add a string containing all the team names to the solution.
         * if the solution set contains more than one element, then it's ambiguous. otherwise, print out the solution
         */
        int minLength = (int) 1e9;
        for (int j = 1; j < n; j++) minLength = Math.min(minLength, input[0][j].length());
        System.out.println(minLength);

        ArrayList<String> answers = new ArrayList<>();
        boolean many = false;
        for (int secondStart = 1; secondStart < minLength; secondStart++) {
            // pw.println("SECOND START = "+secondStart);
            boolean works = true;
            for (int j = 1; j < n && works; j++) {
                if (input[0][j].charAt(secondStart-1) != input[0][1].charAt(secondStart-1)) {
                    works = false;
                }
            }
            if (!works) break;


            for (int i = 1; i < n && works; i++) {
                for (int j = 0; j < n && works; j++) {
                    if (i == j) continue;

                    // pw.println("i = "+i+", j="+j+", input[i][j]="+input[i][j]);
                    int iLength = input[0][i].length() - secondStart;
                    int jLength = j == 0
                        ? secondStart
                        : input[0][j].length() - secondStart;
                    // pw.println("ilength = "+iLength+", jlen = "+jLength);
                    for (int k = 0; k < input[i][j].length() && works; k++) {
                        if (input[i][j].length() != iLength + jLength) {
                            works = false;
                            break;
                        }

                        if (k < iLength) {
                            // if (j == 0) {
                            //     //
                            // } else {
                            //     //
                            // }

                            if (input[0][i].charAt(secondStart + k) != input[i][j].charAt(k)) {
                                works = false;
                            }
                        } else {
                            int idx = k - iLength;
                            if (j == 0) {
                                if (input[0][1].charAt(idx) != input[i][j].charAt(k)) {
                                    works = false;
                                }
                            } else {
                                if (input[0][j].charAt(secondStart + idx) != input[i][j].charAt(k)) {
                                    works = false;
                                }
                            }
                        }

                        // if (j == 0) {
                        //     if (input[0][1].charAt(idx) != input[i][j].charAt(k)) {
                        //         works = false;
                        //     }
                        // } else {
                        //     if (input[0][j].charAt(secondStart + idx) != input[i][j].charAt(k)) {
                        //         works = false;
                        //     }
                        // }
                    }
                }
            }

            if (works) {
                if (!answers.isEmpty()) {
                    many = true;
                    break;
                }
                StringBuilder solution = new StringBuilder();
                solution.append(input[0][1].substring(0, secondStart));
                for (int j = 1; j < n; j++) {
                    solution.append(";");
                    solution.append(input[0][j].substring(secondStart));
                }
                answers.add(solution.toString());
            }
        }

        if (answers.size() == 0) {
            pw.println("NONE");
        } else if (many) {
            pw.println("MANY");
        } else {
            pw.println("UNIQUE");
            String a = answers.get(0);
            // for (String a : answers) {
                String[] names = a.split(";");
                for (String name : names) {
                    pw.println(name);
                }
                // break;
            // }
        }
    }
}