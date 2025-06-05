# assumes that there are 12 digits and no spaces in the input
def checksum(num):
    digitList = str(num)
    sum = 0
    for i in range(6):
        sum += int(digitList[2 * i])
        sum += 3 * int(digitList[2 * i + 1])
    result = (10 - (sum % 10)) % 10
    return result

print(checksum("000000200040"))
print(checksum(978093569967) )

# ====================

# for x in range(10):
#     for y in range(10):
#         if ((3 * x + y) % 10 == (3 * y + x) % 10):
#             print(f"x={x} and y={y}")

# ====================

# def check(x, y):
#     x = str(x)
#     y = str(y)
#     sumX = 3 * int(x[0]) + int(x[1])
#     sumY = 3 * int(y[0]) + int(y[1])
#     sumX2 = int(x[0]) + 3 * int(x[1])
#     sumY2 = int(y[0]) + 3 * int(y[1])
#     if (sumX == sumY):
#         print(f"Multiplying the first digit by 3 and the second by 1. Equal when x={x} and y={y}.")
#     if (sumX2 == sumY2):
#         print(f"Multiplying the first digit by 1 and the second by 3. Equal when x={x} and y={y}.")

# check(13, 30)
# check(14, 40)
# check(15, 50)
# check(16, 60)
# check(17, 70)
# check(18, 80)
# check(19, 90)