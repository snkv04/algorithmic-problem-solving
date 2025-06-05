nums = list(map(int, input().split()))
nums.sort()
d = {}
d["A"] = 0
d["B"] = 1
d["C"] = 2
order = input()
for i in range(3):
    print(f"{nums[d[order[i]]]} ", end="")