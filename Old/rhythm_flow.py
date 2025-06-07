n,m=map(int,input().split())
v=[int(input()) for _ in range(n*m)]
p={1e9:0,102:2,43:4,23:6,15:7}
dp=[[0]*(m+1) for _ in range(n+1)]
for i in range(n):
 for j in range(m):
  d=abs(v[i]-v[n+j])
  dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j],dp[i][j]+(max(p[k] for k in p if k>=d)))
print(dp[n][m])