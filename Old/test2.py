# # def matrixMultiplication(m1, m2):
# #     n = len(m1)
# #     arr = []
# #     for i in range(n):
# #         temp = 0
# #         for k in range(len(m1[0])):
# #             temp += m1[i][k] * m2[k][i]
# #         arr.append(temp)

# #     for j in range(n):
# #         temp = 0
# #         for k in range(len(m1[0])):
# #             temp += m1[0][k] * m2[k][j]
# #         arr.append(temp)

# #     for i in range(n):
# #         temp = 0
# #         for k in range(len(m1[0])):
# #             temp += m1[i][k] * m2[k][0]
# #         arr.append(temp)

# #     return arr

# # import pprint
# # import numpy as np
# # a = [[1,2,3],[4,5,6],[7,8,9]]
# # b = [[10,11,12],[13,14,15],[16,17,18]]
# # print(f"a =\n{np.array(a)}")
# # print(f"b =\n{np.array(b)}")
# # ab = matrixMultiplication(a, b)
# # print(f"ab =\n{np.array(ab)}")


# from scipy.stats import wilcoxon
# import random

# # Example data: Before and after measurements
# # before = [10, 29, 9, 15, 14]
# # after = [8, 11, 10, 13, 12]
# # after = [11, 20, 10, 17, 15]
# # for i in range(len(after)):
# #     after[i] += 100

# # Perform the Wilcoxon Signed-Rank Test
# before = [random.random() * 4 + 25.0 for _ in range(40)]
# after = []; after.extend(before)
# for i in range(40):
#     after[i] += (-0.0000000001 if i < 39 else 100)
# # after[5] += 0.00005
# # for i in range(60):
# #     before[i] *= 2
# #     after[i] *= 2
# print(f"before = {before}, after = {after}")
# res = wilcoxon(x=before, y=after, alternative="greater")
# print(f"type = {type(res)}")
# stat, p = res
# print(f"Statistic: {stat}, p-value: {p}")

# # Interpret the result
# if p < 0.05:
#     print("Significant difference between paired samples (reject H0).")
# else:
#     print("No significant difference (fail to reject H0).")

import time
import multiprocessing

def t2(num, orig, id):
    print(f"from {orig} {id}: {num}")

def t(mx, id):
    for i in range(mx):
        with multiprocessing.Pool(processes=4) as pool:
            args_list = [[j, i, id] for j in range(5)]
            results = pool.starmap(t, args_list)
            print(f"finished {i} {id}: {results}")

if __name__ == "__main__":
    with multiprocessing.Pool(processes=4) as pool:
        args_list = [[5, chr(ord('a') + i)] for i in range(5)]
        results = pool.starmap(t, args_list)
        print(f"results = {results}")
        print(f"hello")
