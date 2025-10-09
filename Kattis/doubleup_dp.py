# thang/maceo's code (not mine)

import math
n = int(input())
dp_size = 8
nums = (list(map(lambda x: int(math.log(int(x), 2)), input().split() )))
nums = [0] + nums
dp = [[0] * dp_size for _ in range(n+1)]

for i in range(1, n+1):
    p = i
    dp[i][nums[i]] = i
    for j in range(nums[i] + 1, dp_size):
        if dp[i][j-1] != 0 or p != 0:
            dp[i][j] = dp[p - 1][j - 1]
            p = dp[i][j];
    for j in range(0, dp_size):
        dp[i][j] = max(dp[i][j], dp[i-1][j])
largest = 0
for i in range(dp_size):
    if dp[n][i] != 0:
        largest = max(largest, i)

for i in range(0, n+1):
    print(f"dp[{i}] = {dp[i]}")

print(2**largest)
