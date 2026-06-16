t = int(input())
while t > 0:
    n = int(input())
    a = map(int, input().split())

    b = set()
    for ai in a:
        b.add(ai)
    print("YES" if 100 in b else "NO")

    t -= 1
