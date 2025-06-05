t = int(input())
while t > 0:
    n = int(input())
    s = input()
    count = 0
    for i in range(n):
        if (s[i] == '1'): count += 1
    print("NO" if count == n else "YES")

    t -= 1