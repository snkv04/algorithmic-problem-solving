import math
from functools import lru_cache

n = int(input())
values = {'J': 11, 'Q': 12, 'K': 13, 'A': 1, 'T': 10}
def convert_input(line):
    temp = []
    for i in range(len(line)):
        if line[i] in '23456789':
            temp.append(int(line[i]))
        else:
            temp.append(values[line[i]])
    return temp

cards = []
while n > 0:
    line = convert_input(input().split())
    n -= len(line)
    cards.extend(line)
n = len(cards)
cards = sorted(cards)
# print(cards)

@lru_cache(maxsize=None)
def count_fifteens(i, curr):
    # if i >= len(cards):
    #     return 0
    # card = cards[i] if cards[i] <= 9 else 10
    # if curr + card > 15:
    #     return 0
    # if curr + card == 15:
    #     return 1 + count_fifteens(i+1, curr)
    # return count_fifteens(i+1, curr + card) + count_fifteens(i+1, curr)
    combos = []
    combos.append(1)
    for i in range(15):
        combos.append(0)
    for card in cards:
        actual = min(card, 10)
        for sum in range(15, 0, -1):
            if sum - actual >= 0:
                combos[sum] += combos[sum-actual]
    return int(combos[15])

def count_pairs():
    mp = dict()
    total = 0
    for card in cards:
        if card in mp:
            mp[card] += 1
        else:
            mp[card] = 1
    for entry in mp.items():
        count = entry[1]
        total += (count * (count-1)) / 2
    return int(total)


def count_runs():
    # def helper(i):
    #     prev = i
    #     duplicates = {}
    #     length = 1
    #     for curr in range(i + 1, len(cards)):
    #         if cards[curr] == cards[prev] + 1:
    #             length += 1
    #             prev = curr
    #         elif cards[curr] == cards[prev]:
    #             prev = curr
    #             duplicates[cards[prev]] = duplicates.get(cards[prev], 1) + 1
    #         else:
    #             break

    #     if length >= 3:
    #         multiple = 1
    #         for count in duplicates.values():
    #             multiple *= count
    #         return multiple, length
    #     else:
    #         return 0, 0

    # runs = []
    # i = 0
    # while i < len(cards):
    #     temp, templ = helper(i)
    #     if temp != 0:
    #         runs.append((temp,templ))
    #         i += templ
    #     else:
    #         i+=1    

    # return runs

    mp = dict()
    for card in cards:
        if card in mp:
            mp[card] += 1
        else:
            mp[card] = 1
    # print(f"map = {mp}")

    segments = []
    i = 1
    while i <= 13:
        if i not in mp:
            i += 1
        else:
            j = i
            while j+1 in mp:
                j += 1
            if j - i + 1 >= 3:
                segments.append((i, j))
            
            i = j+1
    # print(segments)
    
    total = 0
    for segment in segments:
        l = segment[0]
        r = segment[1]
        length = r - l + 1
        # if length < 3:
        #     continue
        count = 1
        for card in range(l, r+1):
            count *= mp[card]
        total += count * length
    return int(total)

# runs = count_runs()
# pairs = count_pairs()
# fifteens = count_fifteens(0, 0)
# totalRuns = 0
# # print(f'pairs: {pairs}, fifteens: {fifteens}')
# for num, length in runs:
#     totalRuns += num*length
#     # print(f'{num} run(s) of length {length}')
# # print(totalRuns)
# print(int(fifteens*2 + pairs*2 + totalRuns))

pairs = count_pairs()
fifteens = count_fifteens(0, 0)
runs = count_runs()
print(int(fifteens*2 + pairs*2 + runs))
