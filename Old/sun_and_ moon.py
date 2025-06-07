ds, ys = map(int, input().split())
dm, ym = map(int, input().split())
ds *= -1
dm *= -1
while True:
    if ds < dm:
        ds += ys
    elif dm < ds:
        dm += ym
    else:
        print(ds)
        break