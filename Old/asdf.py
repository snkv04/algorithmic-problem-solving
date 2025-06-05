
def findMax(a,b):
    if a==0:
        return 0
    sum = 0
    while(sum+a<=b):
        sum += a
    return sum

def runTest(i, dividend, j):
    # print(f"in runtest when i={i} and j={j}")
    maxOfJ = findMax(j,i)
    if not((maxOfJ == (maxOfJ % 100))):
        return False

    line4 = i-maxOfJ
    if not(line4 == (line4 % 10)):
        return False

    newLine4 = (line4 * 100) + 28
    if not(newLine4 == (newLine4 % 1000)):
        print("LOL")
        return False
    if not(findMax(j, newLine4) == newLine4):
        return False
    return True

willbreak = False
for i in range(1000):
    dividend = (100 * i) + 28
    for j in range(100):
        if (i<100 or j<10):
            continue
        print(runTest(i,dividend,j))
        print(f"^ finished runtest when i={i} and j={j}\n")
        if runTest(i,dividend,j):
            willbreak=True
            break
    if willbreak:
        break
