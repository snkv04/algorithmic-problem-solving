def countsubsequence(s, t):
    memo = [0] * (len(t) + 1)
    memo[0] = 1
    for i in range(len(s)):
        for j in range(len(t), 0, -1):
            memo[j] += memo[j-1] if s[i] == t[j-1] else 0
            memo[j] %= int(1e9+7)
    return memo[len(t)]

full = input()
regex = input()
rotations = set()
n = len(regex)
for i in range(n):
    str = regex[i:n] + regex[0:i]
    rotations.add(str)
ans = 0
for rot in rotations:
    ans += countsubsequence(full, rot)
    ans %= int(1e9+7)
print(ans)