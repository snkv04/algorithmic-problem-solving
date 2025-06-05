s=input()
n=len(s)
i=n
m=[0]*n;o=[0]*n
while i>0:
 i-=1
 q=[m[j]for j in range(i+1,n)if s[i]<s[j]]
 x=0 if len(q)==0 else max(q)
 m[i]=1+x

i=0
while i<n:
 q=[o[j]for j in range(i)if s[j]<s[i]]
 x=0 if len(q)==0 else max(q)
 o[i]=1+x
 i+=1

a=0
for k in range(n):a=max(a,m[k]+o[k]-1)
print(26-a)

# static void solve() throws IOException {
#         char[] s = br.readLine().toCharArray();
#         int n = s.length;
#         ArrayList<Integer>[] adj = new ArrayList[n], adj2 = new ArrayList[n];
#         for (int i = 0; i < n; i++) { adj[i] = new ArrayList<>(); adj2[i] = new ArrayList<>(); }
#         for (int i = 0; i <= n-1; i++) {
#             for (int j = i+1; j <= n-1; j++) {
#                 if (s[i] < s[j]) {
#                     adj[i].add(j);
#                     adj2[j].add(i);
#                 }
#             }
#         }

#         int[] memo = new int[n], memo2 = new int[n];
#         for (int i = n-1; i >= 0; i--) {
#             int max = 0;
#             for (int next : adj[i]) {
#                 max = Math.max(max, memo[next]);
#             }
#             memo[i] = 1 + max;
#         }
#         for (int i = 0; i <= n-1; i++) {
#             int max = 0;
#             for (int next : adj2[i]) {
#                 max = Math.max(max, memo2[next]);
#             }
#             memo2[i] = 1 + max;
#         }

#         int best = 0;
#         for (int i = 0; i <= n-1; i++) {
#             best = Math.max(best, memo[i] + memo2[i] - 1);
#         }
#         pw.println(26-best);
#     }