t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    dist = 0
    for i in range(1, n):
        dist += a[i] - a[i-1]
        dist += a[2*n-i] - a[2*n-1-i]
    print(dist)
    for i in range(n):
        print(f"{a[i]} {a[2*n-1-i]}")