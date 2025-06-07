for i in range(40):
    original = int(input())
    s = list()
    while original > 0:
        s.append(original % 2)
        original //= 2
    for j in  range(len(s)-1, -1, -1):
        print(s[j], end="")
    print()
    