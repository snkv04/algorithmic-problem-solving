t = int(input())
for _ in range(t):
    n, a, q = map(int, input().split())
    mx = a
    poss = a
    s = input()
    for char in s:
        if char == "+":
            poss += 1
            a += 1
            mx = max(mx, a)
        else:
            a -= 1
    if mx == n:
        print("YES")
    elif poss >= n:
        print("MAYBE")
    else: print("NO")
