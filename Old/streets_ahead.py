n,q=map(int,input().split())
d={input():i for i in range(n)}
while q>0:f,s=input().split();print(abs(d[f]-d[s])-1);n-=1