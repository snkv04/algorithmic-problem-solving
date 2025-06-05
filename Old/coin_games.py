for i in range(int(input())): _ = int(input()); print("no" if sum([c == "U" for c in input()]) % 2 == 0 else "yes")
