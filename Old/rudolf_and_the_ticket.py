t = int(input())
while t > 0:
    n, m, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    b.sort()
    count = 0
    for ai in a:
        l, r = 0, m - 1
        index = -1
        while l <= r:
            mid = (l + r) // 2
            if b[mid] + ai <= k:
                index = mid
                l = mid + 1
            else: 
                r = mid - 1
        count += index + 1
    print(count)
    t -= 1