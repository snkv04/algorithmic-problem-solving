import math

def shift(x_orig):
    x = x_orig[:]

    if x[0] == 0:
        return x
    
    # print(x, "before")
    while abs(x[0]) < 10**9:
        x[0] *= 10
        x[1] -= 1
    while abs(x[0]) >= 10**10:
        # print(x)
        x[0] //= 10
        x[1] += 1
    # print(x, "after")
    return x

def add(x_orig, y_orig):
    x, y = x_orig[:], y_orig[:]

    if x[1] < y[1]:
        x, y = y, x
    
    if x[1] >= y[1] + 10:
        return x
    
    scale_diff = x[1] - y[1]
    while scale_diff > 0:
        y[0] //= 10
        y[1] += 1
        scale_diff -= 1
    while scale_diff < 0:
        y[0] *= 10
        y[1] -= 1
        scale_diff += 1
    x[0] += y[0]
    return x
    
def sub(x_orig, y_orig):
    x, y = x_orig[:], y_orig[:]
    if x[1] >= y[1] + 10:
        return x
    if y[1] >= x[1] + 10:
        return [-1 * y[0], y[1]]
    
    scale_diff = x[1] - y[1]
    while scale_diff > 0:
        y[0] //= 10
        y[1] += 1
        scale_diff -= 1
    while scale_diff < 0:
        y[0] *= 10
        y[1] -= 1
        scale_diff += 1
    x[0] -= y[0]
    return x

def mult(x_orig, y_orig):
    x, y = x_orig[:], y_orig[:]

    x[0] *= y[0]
    x[0] //= 10**9
    x[1] += y[1]
    return x

def div(x_orig, y_orig):
    x, y = x_orig[:], y_orig[:]

    if x[0] == 0:
        return [0, 0]

    # print(f"x[0] = {x[0]}, y[0] = {y[0]}")
    x[0] = ((x[0]* 10**9)/(y[0] * 10**9))
    x[0] *= 10**9
    x[1] -= y[1]
    # print("about to shift")
    return x

def error_good(correct_orig, student_orig):
    correct = correct_orig[:]
    student = student_orig[:]

    # print(f"correct = {correct}, stduent = {student}")

    if correct[0] == 0:
        return student[0] == 0

    subbed = shift(sub(correct, student))
    # print(f"sub = {sub(correct, student)}")
    abs_good = (subbed[0] == 0) or subbed[1] < -9
    # print(f"abs_good = {abs_good}")

    diff = sub(correct, student)
    diff[0] = abs(diff[0])
    correct[0] = abs(correct[0])
    rel_error = shift(div(diff, correct))
    rel_good = (rel_error[0] == 0) or rel_error[1] < -9

    return abs_good and rel_good

    
if __name__ == "__main__":
    s = input().split('e')
    x = [int(float(s[0]) * 10**9), int(s[1])]
    s = input().split('e')
    y = [int(float(s[0]) * 10**9), int(s[1])]

    s = input().split('e')
    student_add = [int(float(s[0]) * 10**9), int(s[1])]
    s = input().split('e')
    student_sub = [int(float(s[0]) * 10**9), int(s[1])]
    s = input().split('e')
    student_mult = [int(float(s[0]) * 10**9), int(s[1])]
    s = input().split('e')
    student_div = [int(float(s[0]) * 10**9), int(s[1])]

    added = add(x, y)
    subbed = sub(x, y)
    multed = mult(x, y)
    divved = div(x, y)

    for pair in [(added, student_add), (subbed, student_sub), (multed, student_mult), (divved, student_div)]:
        correct = pair[0]
        student = pair[1]
        
        print("Correct" if error_good(correct, student) else "Incorrect")

    # print(add(x, y))
    # print(sub(x, y))
    # print(mult(x, y))
    # print(div(x, y))
