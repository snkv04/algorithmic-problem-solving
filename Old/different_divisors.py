sieved = set()
for i in range(1, 20002):
    sieved.add(i)
for i in range(2, 151):
    x = 2
    while True:
        if i*x>20001: break

        if (i*x in sieved): sieved.remove(i*x)
        x += 1
sieved = list(sieved)
sieved.sort()

t = int(input())
while t > 0:
    d = int(input())
    (l, r, num1) = (0, len(sieved)-1, -1)
    # print(f"l1={l}, r1={r}")
    while l <= r:
        mid = (l + r) // 2
        if (sieved[mid] >= 1+d):
            num1 = sieved[mid]
            r = mid-1
        else:
            l = mid+1
    l, r, num2 = (0, len(sieved)-1, -1)
    # print(f"l2={l}, r2={r}")
    while l <= r:
        mid = (l+r) // 2
        if (sieved[mid] >= 1 + 2*d):
            num2 = sieved[mid]
            r = mid-1
        else:
            l = mid+1
    num2 = min(num2, num1*num1)
    print(num1*num2)

    t-=1