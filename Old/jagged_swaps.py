t = int(input())
while t > 0:
    n = int(input())
    a = list(map(int, input().split()))
    print("YES" if a[0] == 1 else "NO")

    t -= 1