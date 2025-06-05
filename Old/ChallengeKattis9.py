def gcd(a, b):
    A = max(a, b)
    B = min(a, b)
    while B != 0:
        temp = A%B
        A = B
        B = temp
    return A

a, b, c = map(int, input().split())
product = a*b
gcd = gcd(product, c)
product /= gcd
c /= gcd
print(float(product)/float(c))