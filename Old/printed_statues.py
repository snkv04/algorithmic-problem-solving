n = int(input())
ans = 0
while (1 << ans) < n:
    ans += 1
print(ans+1)