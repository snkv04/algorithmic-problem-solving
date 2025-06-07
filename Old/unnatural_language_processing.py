t = int(input())
for _ in range(t):
    n = int(input())
    c = {'b', 'c', 'd'}
    s = input()
    is_start = [False] * n
    last = n
    for i in range(n-1, -1, -1):
        if last-i >= 2 and s[i] in c:
            last = i
            is_start[i] = True
    for i in range(n):
        if (i != 0 and is_start[i]): print(".", end="")
        print(s[i], end="")
    print()