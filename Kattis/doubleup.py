n = int(input())
a = list(map(int, input().split()))

ans, curr = 1, 1
while len(a):
    b = []
    i = 0
    while i < len(a):
        if a[i] > curr:
            b.append(a[i])
            i += 1
        else:
            if i < len(a) - 1 and a[i+1] == a[i]:
                b.append(2 * a[i])
                i += 2
            else:
                i += 1

    ans = max(ans, b[0] if len(b) else 0)
    curr *= 2
    a = b
print(ans)
