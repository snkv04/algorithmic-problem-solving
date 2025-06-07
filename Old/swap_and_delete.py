t = int(input())
while t > 0:
    s = input()
    ones = []
    zeros = []
    for i in range(len(s)):
        ones.append((0 if i==0 else ones[-1]) + (1 if s[i]=='1' else 0))
        zeros.append((0 if i==0 else zeros[-1]) + (1 if s[i]=='0' else 0))
    # print(ones)
    # print(zeros)
    ans = -1
    n = len(s)
    for i in range(len(s)):
        needed_ones = zeros[n-1-i]
        needed_zeros = ones[n-1-i]
        if needed_ones <= ones[n-1] and needed_zeros <= zeros[n-1]:
            diff = ones[n-1]-needed_ones + zeros[n-1]-needed_zeros
            if diff == i:
                ans = i
                break
    print(ans if ans != -1 else n)
    t -= 1