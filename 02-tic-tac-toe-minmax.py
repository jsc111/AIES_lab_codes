import math

# Generic player constants
PLAYER1 = -1
PLAYER2 = 1

def create_board(size):
    return [[0 for _ in range(size)] for _ in range(size)]

def print_board(board):
    chars = {0: ' ', PLAYER1: 'X', PLAYER2: 'O'}
    for row in board:
        print('|'.join(chars[cell] for cell in row))
        print('-' * (len(board) * 2 - 1))

def check_win(board, player):
    size = len(board)
    # Check rows, columns, and diagonals
    win_condition = [player] * size
    for i in range(size):
        if board[i] == win_condition or [board[j][i] for j in range(size)] == win_condition:
            return True
    if [board[i][i] for i in range(size)] == win_condition or [board[i][size-i-1] for i in range(size)] == win_condition:
        return True
    return False

def evaluate(board):
    if check_win(board, PLAYER2):
        return 1
    elif check_win(board, PLAYER1):
        return -1
    else:
        return 0

def is_moves_left(board):
    return any(0 in row for row in board)

def minimax(board, depth, is_max):
    score = evaluate(board)
    if score != 0:
        return score
    if not is_moves_left(board):
        return 0

    best = -math.inf if is_max else math.inf
    for i in range(len(board)):
        for j in range(len(board)):
            if board[i][j] == 0:
                board[i][j] = PLAYER2 if is_max else PLAYER1
                current_score = minimax(board, depth + 1, not is_max)
                best = max(best, current_score) if is_max else min(best, current_score)
                board[i][j] = 0
    return best

def find_best_move(board):
    best_val = -math.inf
    best_move = (-1, -1)
    for i in range(len(board)):
        for j in range(len(board)):
            if board[i][j] == 0:
                board[i][j] = PLAYER2
                move_val = minimax(board, 0, False)
                board[i][j] = 0
                if move_val > best_val:
                    best_move = (i, j)
                    best_val = move_val
    return best_move

def main():
    size = int(input("Enter the board size (e.g., 3 for 3x3): "))
    board = create_board(size)
    
    while is_moves_left(board):
        print_board(board)
        x, y = map(int, input("Enter your move (row and column): ").split())
        if board[x][y] != 0:
            print("Invalid move, try again.")
            continue
        board[x][y] = PLAYER1
        if check_win(board, PLAYER1):
            print("You win!")
            break
        elif not is_moves_left(board):
            print("Draw!")
            break
        move = find_best_move(board)
        board[move[0]][move[1]] = PLAYER2
        if check_win(board, PLAYER2):
            print("AI wins!")
            break
        elif not is_moves_left(board):
            print("Draw!")
            break
    print_board(board)

if __name__ == "__main__":
    main()
