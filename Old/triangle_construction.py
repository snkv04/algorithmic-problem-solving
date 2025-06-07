n = int(input())
a = list(map(int, input().split()))
max = max(a)
sum = sum(a)
if max <= 2*(sum-max):
    print(sum // 3)
else:
    print(sum-max)