class Solution:
    # O(n) complexity
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        nums_multiset = {}
        for i in range(len(nums)):
            if nums[i] in nums_multiset:
                nums_multiset[nums[i]] += 1
            else:
                nums_multiset[nums[i]] = 1
        
        addend1 = 0
        addend2 = 0
        for i in range(len(nums)):
            remaining = target - nums[i]
            if remaining in nums_multiset:
                if nums[i] == remaining and nums_multiset[remaining] == 1:
                    continue
                addend1 = nums[i]
                addend2 = remaining
                break
        
        k = 0
        result = []
        while len(result) < 2:
            if addend1 == nums[k] or addend2 == nums[k]:
                result.append(k)
            k += 1
        
        return result