class Solution:
    def maximizeSquareArea(self, m: int, n: int, hFences: List[int], vFences: List[int]) -> int:
        hFences.insert(0, 1)
        hFences.append(m)
        vFences.insert(0, 1)
        vFences.append(n)

        intersections = dict()
        for h in hFences:
            for v in vFences:
                diag = h + v
                if diag not in intersections:
                    intersections[diag] = [h, h]
                intersections[diag][0] = min(intersections[diag][0], h)
                intersections[diag][1] = max(intersections[diag][1], h)
        

        ans = 0
        for diag in intersections:
            leftmost, rightmost = intersections[diag]
            dist = rightmost - leftmost
            ans = max(ans, dist * dist)

        if ans == 0:
            return -1
        else:
            ans %= int(1e9 + 7)
            return int(ans)
