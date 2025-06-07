t = int(input())
while t > 0:
    n, q = tuple(map(int, input().split()))
    a = list(map(int, input().split()))
    pref_sums = [0]
    for i in range(n):
        pref_sums.append(pref_sums[-1]+a[i])
    while q > 0:
        l, r, k = tuple(map(int, input().split()))
        sum = pref_sums[n] - pref_sums[r] + pref_sums[l-1]
        sum += k * (r-l+1)
        print("YES" if sum % 2 == 1 else "NO")
        q -= 1
    t -= 1