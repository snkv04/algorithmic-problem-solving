def make_move(board, source, target):
    new_board = list(board)
    new_board[source] = '.'
    new_board[target] = board[source]
    return ''.join(new_board)

def isWinning(board, isFirst):
    possible = []
    for i in range(len(board)-1):
        if (board[i] == 'B' and board[i+1] == 'W') or (board[i] == 'W' and board[i+1] == 'B'):
            possible.append((i, i+1))
    
    if not possible:
        return not isFirst

    for i, j in possible:
        newBoardL = make_move(board, i, j)
        newBoardR = make_move(board, j, i)
        return isWinning(newBoardL, not isFirst) or isWinning(newBoardR, not isFirst)
    
    return False


N = int(input())
board = input().strip()

winning = []
possible = []
for i in range(N-1):
    if (board[i] == 'B' and board[i+1] == 'W') or (board[i] == 'W' and board[i+1] == 'B'):
        possible.append((i, i+1))

for i, j in possible:
    newBoardL = make_move(board, i, j)
    if isWinning(newBoardL, False):
        winning.append((i+1,j+1))
    
    newBoardR = make_move(board, j, i)
    if isWinning(newBoardR, False):
        winning.append((j+1, i+1))

winning = sorted(winning)
print(len(winning))
for i, j in winning:
    print(i,j)