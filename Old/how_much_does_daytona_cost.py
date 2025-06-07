t = int(input())
while t > 0:
    _, k = map(int, input().split())
    a = list(map(int, input().split()))
    there = False
    for num in a:
        if num == k:
            there = True
            break
    print("yes" if there else "no")

    t -= 1