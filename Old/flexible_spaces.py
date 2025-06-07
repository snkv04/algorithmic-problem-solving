w, p = map(int, input().split())
partitions = list(map(int, input().split()))
partitions.append(0)
partitions.append(w)
partitions.sort()
rooms = set()
for i in range(p+2):
    for j in range(i+1, p+2):
        rooms.add(partitions[j]-partitions[i])
rooms = list(rooms)
rooms.sort()
for len in rooms: print(len, end=" ")