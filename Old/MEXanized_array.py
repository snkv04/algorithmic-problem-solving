t = int(input())
while t > 0:
    n, k, x = map(int, input().split())
    if x < k-1:
        print(-1)
        t -= 1
        continue
    sum = 0
    for i in range(x+1):
        if i == k or n == 0:
            continue
        sum += i
        n -= 1
    sum += n * (x if x != k else x-1)
    print(sum)
    print(f"HERE({sum})")

    t -= 1