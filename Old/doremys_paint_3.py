t = int(input())
while t > 0:
    n = int(input())
    a = map(int, input().split())
    freq = dict()
    for char in a:
        if char not in freq:
            freq[char] = 1
        else:
            freq[char] += 1
    
    if len(freq) == 1:
        print("yes")
    elif len(freq) > 2:
        print("no")
    else:
        counts = list()
        for char in freq:
            counts.append(freq[char])
        counts.sort()
        if counts[0] == n // 2 and counts[1] == (n+1) // 2:
            print("yes")
        else:
            print("no")

    t -= 1