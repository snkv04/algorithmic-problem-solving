n, k = tuple(map(int, input().split()))
min = 0
max = 0
for i in range(k):
    rating = int(input())
    min += rating
    max += rating
min += (-3) * (n-k)
max += 3 * (n-k)
min /= n
max /= n
print(f"{min} {max}")