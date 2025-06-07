t = int(input())
while t > 0:
    x, y, k = tuple(map(int, input().split()))
    if (x >= y):
        print(x)
    elif x+k>=y:
        print(y)
    else:
        print(x+k+2*(y-x-k))
    t -= 1