import sys
import math

# ---------- gcd & lcm ----------

def gcd(a, b):
    a = abs(a)
    b = abs(b)
    A = max(a, b)
    B = min(a, b)
    while B != 0:
        R = A % B
        A = B
        B = R
    return A

def lcm(a, b):
    return a // gcd(a, b) * b


# ---------- Fraction class (Frac) ----------

class Frac:
    def __init__(self, num, denom=1):
        self.num = num
        self.denom = denom
        self.reduce()

    # --- comparison operators ---
    def __lt__(self, other):
        d = lcm(self.denom, other.denom)
        if d < 0:
            d = -d
        n1 = self.num * (d // self.denom)
        n2 = other.num * (d // other.denom)
        return n1 < n2

    def __eq__(self, other):
        f1 = Frac(self.num, self.denom)
        f2 = Frac(other.num, other.denom)
        return f1.num == f2.num and f1.denom == f2.denom

    def __ne__(self, other):
        return not (self == other)

    def __le__(self, other):
        return self < other or self == other

    # --- normalization ---
    def reduce(self):
        g = gcd(self.num, self.denom)
        self.num //= g
        self.denom //= g
        if self.denom < 0:
            self.num = -self.num
            self.denom = -self.denom

    # --- arithmetic operators ---
    def __add__(self, other):
        d = lcm(self.denom, other.denom)
        if d < 0:
            d = -d
        n1 = self.num * (d // self.denom)
        n2 = other.num * (d // other.denom)
        return Frac(n1 + n2, d)

    def __sub__(self, other):
        return self + (Frac(-1) * other)

    def __mul__(self, other):
        return Frac(self.num * other.num, self.denom * other.denom)

    def __truediv__(self, other):
        return Frac(self.num * other.denom, self.denom * other.num)

    # extra method from C++
    def sign(self):
        self.reduce()
        if self.num == 0:
            return 0
        elif self.num > 0:
            return 1
        else:
            return -1

    # for printing
    def __repr__(self):
        return f"{self.num}/{self.denom}"


# ---------- Point ----------

class Point:
    def __init__(self, x, y):
        if not isinstance(x, Frac):
            x = Frac(x)
        if not isinstance(y, Frac):
            y = Frac(y)
        self.x = x
        self.y = y

    def __lt__(self, other):
        if self.x != other.x:
            return self.x < other.x
        return self.y < other.y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        # since Frac always normalized, hash is safe
        return hash((self.x.num, self.x.denom, self.y.num, self.y.denom))

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __repr__(self):
        return f"({self.x}, {self.y})"


# ---------- cross product ----------

def cross(a, b):
    return a.x * b.y - a.y * b.x


# ---------- Line ----------

class Line:
    def __init__(self, x1, y1, x2, y2):
        self.s = Point(x1, y1)
        self.e = Point(x2, y2)
        if self.e < self.s:
            self.s, self.e = self.e, self.s

    def slope(self):
        num = self.e.y - self.s.y
        denom = self.e.x - self.s.x
        result = num / denom
        result.reduce()
        return result

    def yint(self):
        return self.s.y - self.slope() * self.s.x

    def __repr__(self):
        return f"[{self.s} to {self.e}]"


# ---------- solve() ----------

def solve():
    n = int(sys.stdin.readline())
    lines = []

    for _ in range(n):
        x1, y1, x2, y2 = map(int, sys.stdin.readline().split())
        lines.append(Line(x1, y1, x2, y2))

    isects = set()
    zero = Frac(0, 1)

    for i in range(n):
        l1 = lines[i]
        for j in range(i + 1, n):
            l2 = lines[j]

            # ----- collinear vertical case -----
            if l1.s.x == l1.e.x and l2.s.x == l2.e.x:
                if l1.s.x == l2.s.x:
                    if l1.s.y == l2.e.y:
                        isects.add(Point(l1.s.x, Frac(l1.s.y)))
                        continue
                    elif l1.e.y == l2.s.y:
                        isects.add(Point(l1.s.x, l1.e.y))
                        continue
                    elif max(l1.s.y, l2.s.y) <= min(l1.e.y, l2.e.y):
                        print(-1)
                        return
                    else:
                        continue
                else:
                    continue

            # ----- collinear non-vertical -----
            if l1.s.x != l1.e.x and l2.s.x != l2.e.x and (l1.slope() == l2.slope()):
                if l1.yint() == l2.yint():
                    if l1.s.x == l2.e.x:
                        isects.add(Point(l1.s.x, l1.s.y))
                        continue
                    elif l1.e.x == l2.s.x:
                        isects.add(Point(l1.e.x, l1.e.y))
                        continue
                    elif max(l1.s.x, l2.s.x) <= min(l1.e.x, l2.e.x):
                        print(-1)
                        return
                    else:
                        continue
                else:
                    continue

            # ----- general segment intersection test -----
            ab = l1.e - l1.s
            ac = l2.s - l1.s
            ad = l2.e - l1.s
            cd = l2.e - l2.s
            ca = l1.s - l2.s
            cb = l1.e - l2.s

            c1 = cross(ab, ac).sign()
            c2 = cross(ab, ad).sign()
            c3 = cross(cd, ca).sign()
            c4 = cross(cd, cb).sign()

            if c1 * c2 <= 0 and c3 * c4 <= 0:
                # one unique intersection point
                if l1.s.x == l1.e.x:
                    m = l2.slope()
                    b = l2.yint()
                    y = m * l1.s.x + b
                    isects.add(Point(l1.s.x, y))
                elif l2.s.x == l2.e.x:
                    m = l1.slope()
                    b = l1.yint()
                    y = m * l2.s.x + b
                    isects.add(Point(l2.s.x, y))
                else:
                    m1 = l1.slope()
                    b1 = l1.yint()
                    m2 = l2.slope()
                    b2 = l2.yint()
                    x = (b2 - b1) / (m1 - m2)
                    y = m1 * x + b1
                    isects.add(Point(x, y))

    print(len(isects))


# ---------- main ----------

if __name__ == "__main__":
    solve()
