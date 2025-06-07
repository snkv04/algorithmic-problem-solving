t = int(input())
while t > 0:
    n, k = tuple(map(int, input().split()))
    s = input()
    a = []
    b = []
    for i in range(n):
        if s[i] == 'A':
            a.append(i+1)
        else:
            b.append(i+1)
    diff = len(b) - k
    if diff > 0:
        print(f"1\n{b[diff-1]} A")
    elif diff < 0:
        print(f"1\n{a[abs(diff)-1]} B")
    else: print(0)
    t -= 1