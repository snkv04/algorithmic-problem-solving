n = int(input())
points = []
for i in range(n):
    x, y = map(int, input().split())
    points.append((x, y))

ans = 0
for t in range(2):
    points = sorted(points, key=lambda p: p[0])

    curr = 0
    for i in range(1, n):
        curr += i * (points[i][0] - points[i - 1][0])
        ans += curr

    for i in range(n):
        points[i] = (points[i][1], points[i][0])
print(ans)
