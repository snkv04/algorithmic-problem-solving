import math

r, s, h = map(int, input().split())
print(r, s, h)
days_per_year = float(2 * math.pi * r) / float(s * h)
dec = min(abs(days_per_year - math.floor(days_per_year)), abs(days_per_year-math.ceil(days_per_year)))
print(dec)
# dec = 0.24219

l, r, n1 = 2, 1000, -1
while l <= r:
    mid = (l + r) // 2
    if 1.0 / mid >= dec:
        n1 = mid
        l = mid+1
    else:
        r = mid-1

# num, denom = 1, n1

l, r, n2 = 1, int(math.floor(1000.0 / n1)), -1
while l <= r:
    mid = (l + r) // 2
    new_val = (1 / float(n1)) - (1 / float(n1*mid))
    if new_val <= dec:
        n2 = mid
        l = mid+1
    else:
        r = mid-1
print(n1, n2, (1 / float(n1)) - (1 / float(n1*n2)))
    
# num, denom = 1 * n2, n1 * n2

l, r, n3 = 1, int(math.floor(1000.0 / (n1 * n2))), -1
while l <= r:
    mid = (l + r) // 2
    new_val = (1 / float(n1)) - (1 / float(n1*n2)) + (1 / float(n1*n2*mid))
    if new_val >= dec:
        n3 = mid
        l = mid+1
    else:
        r = mid-1
print(n1, n2, n3)

