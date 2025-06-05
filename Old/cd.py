while True:
 n,m=map(int,input().split())
 if(n==0 and m==0):break
 a={input()for _ in range(n)}
 b={input()for _ in range(m)}
 ans=0
 for c in a:
  if c in b:ans+=1
 print(ans)