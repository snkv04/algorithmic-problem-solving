t = int(input())
while t > 0:
    n, m, k, H = map(int, input().split())
    h = list(map(int, input().split()))
    ans = 0
    for hi in h:
        diff = abs(H - hi)
        if diff % k == 0 and diff / k >= 1 and diff / k <= m-1:
            ans += 1
    # print(f"here({ans})")
    print(ans)

    t -= 1