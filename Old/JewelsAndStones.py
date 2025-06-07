class Solution:
    def numJewelsInStones(self, jewels: str, stones: str) -> int:
        # O(m * n) complexity
        count = 0
        for i in range(len(jewels)):
            j = 0
            while j <= len(stones) - 1:
                if jewels[i] == stones[j]:
                    count += 1
                    # stones.pop(j)
                    # j -= 1
                j += 1
        return count