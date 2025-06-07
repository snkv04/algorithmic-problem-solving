// import java.util.*;
// import java.io.*;

// public class MooRoute2 {
//     public static void main(String[] args) throws Exception {
//         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//         PrintWriter pw = new PrintWriter(System.out);

//         String[] line = br.readLine().split(" ");
//         int n = Integer.parseInt(line[0]);
//         int m = Integer.parseInt(line[1]);
//         Edge[] edges = new Edge[m];
//         for (int i = 0; i <= m-1; i++) {
//             line = br.readLine().split(" ");
//             int c = Integer.parseInt(line[0]) - 1;
//             int r = Integer.parseInt(line[1]);
//             int d = Integer.parseInt(line[2]) - 1;
//             int s = Integer.parseInt(line[3]);
//             edges[i] = new Edge(c, r, d, s);
//         }
//         int[] layovers = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

//         long[] earliest = new long[n];
//         earliest[0] = 0;
//         for (int i = 1; i <= n-1; i++) {
//             earliest[i] = Long.MAX_VALUE;
//         }
//         for (int i = 1; i <= n; i++) {
//             for (int j = 0; j <= m-1; j++) {
//                 if (edges[j].cj != 0) {
//                     if (earliest[edges[j].cj] + layovers[edges[j].cj] <= edges[j].rj) {
//                         earliest[edges[j].dj] = Math.min(edges[j].sj, earliest[edges[j].dj]);
//                     }
//                     // Edge is = (starting airport, starting time, ending airport, ending time)
//                     // starting place's current time + layover must be ≤ the starting itme of the flight
//                 } else {
//                     // starting airport is airport 0
//                     if (earliest[edges[j].cj] <= edges[j].rj) {
//                         earliest[edges[j].dj] = Math.min(edges[j].sj, earliest[edges[j].dj]);
//                     }
//                 }
//             }
//         }

//         for (int i = 0; i <= n-1; i++) {
//             if (earliest[i] != Long.MAX_VALUE) {
//                 pw.println(earliest[i]);
//             } else {
//                 pw.println(-1);
//             }
//         }

//         br.close(); pw.close();
//     }

//     static class Edge {
//         int cj, rj, dj, sj;

//         public Edge(int c, int r, int d, int s) {
//             cj = c;
//             rj = r;
//             dj = d;
//             sj = s;
//         }
//     }
// }
import java.util.*;
import java.io.*;

public class MooRoute2 {
    static ArrayList<Edge>[] adj;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        adj = new ArrayList[n];
        System.out.println("hello?");
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Edge>();
        }
        System.out.println("adj is populated");
        for (int i = 0; i <= m-1; i++) {
            line = br.readLine().split(" ");
            int c = Integer.parseInt(line[0]) - 1;
            int r = Integer.parseInt(line[1]);
            int d = Integer.parseInt(line[2]) - 1;
            int s = Integer.parseInt(line[3]);
            adj[c].add(new Edge(d, r, s));
        }
        int[] layovers = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

        System.out.println("i am here");

        long[] earliest = new long[n];
        earliest[0] = 0;
        for (int i = 1; i <= n-1; i++) {
            earliest[i] = Long.MAX_VALUE;
        }
        Queue<Integer> q = new LinkedList<Integer>();
        q.add(0);
        while (!q.isEmpty()) {
            int currAirport = q.poll();
            System.out.println("current airport just polled was: "+currAirport);
            for (Edge flight : adj[currAirport]) {
                if (currAirport != 0) {
                    if (earliest[currAirport] + layovers[currAirport] <= flight.startTime) {
                        earliest[flight.endPoint] = Math.min(flight.endTime, earliest[flight.endPoint]);
                        if (!q.contains(flight.endPoint)) {
                            q.add(flight.endPoint);
                        }
                    }
                    // Edge is = (starting airport, starting time, ending airport, ending time)
                    // starting place's current time + layover must be ≤ the starting itme of the flight
                } else {
                    // starting airport is airport 0
                    if (earliest[currAirport] <= flight.startTime) {
                        earliest[flight.endPoint] = Math.min(flight.endTime, earliest[flight.endPoint]);
                        if (!q.contains(flight.endPoint)) {
                            q.add(flight.endPoint);
                        }
                    }
                }
            }
        }

        for (int i = 0; i <= n-1; i++) {
            if (earliest[i] != Long.MAX_VALUE) {
                System.out.println(earliest[i]);
            } else {
                System.out.println(-1);
            }
        }

        br.close(); pw.close();
    }

    static class Edge {
        int endPoint, startTime, endTime;

        public Edge(int d, int r, int s) {
            endPoint = d;
            startTime = r;
            endTime = s;
        }
    }
}
