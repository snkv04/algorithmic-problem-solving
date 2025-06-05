t = int(input())
for _ in range(t):
    n = int(input())
    s = input()
    f = input()
    from1 = 0
    from0 = 0
    for i in range(n):
        if (s[i] != f[i]):
            if (s[i]=='1'): from1 += 1
            else: from0 += 1
    print(max(from1, from0))