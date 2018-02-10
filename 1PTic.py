

from random import randrange

def main():
    space = printIntro()            #Get spaces available from printIntro
    n = 1
    playGame = True

    while playGame:
        if turn(n) == "human":
            moveA, space = getMoveA(space)
            space = updatedBoard(moveA, space)
            if checkWinner(space):
                print("You won! Yey")
                playGame = False
            else:
                if isDraw(space):
                    print("It's a draw!")
                    playGame = False
                else:
                    n = n + 1
        if turn(n) == "comp":
            space = compMoveB(space)
            if checkWinner(space):
                print("Oh no! The computer is smarter than you!")
                playGame = False
            else:
                if isDraw(space):
                    print("It's a draw!")
                    playGame = False
                else:
                    n = n + 1
            
# Log: moveA is when the human places an X
#       moveB is the computer
#       space is the list of places the X's and O's can be.
def printIntro():
    print("Welcome to a friendly game of Tic Tac Toe!")
    print("You are player X and your opponent (comp) is player O.")
    print("Select a space on the matrix by inputting a number from 1 to 9.\n" )
    spaceN = [' ','1','2','3','4','5','6','7','8','9']
    print("-------")
    print("|" + spaceN[1] + "|" + spaceN[2] + "|" + spaceN[3] + "|")
    print("-------")
    print("|" + spaceN[4] + "|" + spaceN[5] + "|" + spaceN[6] + "|")
    print("-------")
    print("|" + spaceN[7] + "|" + spaceN[8] + "|" + spaceN[9] +"|")
    print("-------")
    print("You're up!\n")
    space = [' ',' ',' ',' ',' ',' ',' ',' ',' ',' ']
    return space

def turn(n):
    if n % 2 != 0:
        return "human"
    else: return "comp"
        

def checkWinner(space):
    X = "X"
    O = "O"
    
    return ((space[7] == X and space[8] == X and space[9] == X) or 
    (space[4] == X and space[5] == X and space[6] == X) or 
    (space[1] == X and space[2] == X and space[3] == X) or 
    (space[7] == X and space[4] == X and space[1] == X) or 
    (space[8] == X and space[5] == X and space[2] == X) or 
    (space[9] == X and space[6] == X and space[3] == X) or 
    (space[7] == X and space[5] == X and space[3] == X) or 
    (space[9] == X and space[5] == X and space[1] == X) or
            
    (space[7] == O and space[8] == O and space[9] == O) or 
    (space[4] == O and space[5] == O and space[6] == O) or 
    (space[1] == O and space[2] == O and space[3] == O) or 
    (space[7] == O and space[4] == O and space[1] == O) or 
    (space[8] == O and space[5] == O and space[2] == O) or 
    (space[9] == O and space[6] == O and space[3] == O) or 
    (space[7] == O and space[5] == O and space[3] == O) or 
    (space[9] == O and space[5] == O and space[1] == O))


def freeSpace(space, move):
    # True if no one has put anything there
    return space[move] == ' '

def isDraw(board):
    #True if the board is full (draw)
    for i in range(1, 10):
        if freeSpace(board, i):
            return False
    return True

def getMoveA(space):
    moveA = eval(input("Enter a number corresponding to the matrix.\n>> "))
    return(moveA, space)

def updatedBoard(moveA, space):
    X = "X"
    if space[moveA] == ' ': 
        space[moveA] = X
        print("-------")
        print("|" + space[1] + "|" + space[2] + "|" + space[3] + "|")
        print("-------")
        print("|" + space[4] + "|" + space[5] + "|" + space[6] + "|")
        print("-------")
        print("|" + space[7] + "|" + space[8] + "|" + space[9] +"|")
        print("-------\n")
        return space
   
    else: print("Select an open space."), getMoveA
    

def compMoveB(space):
#How many empty spaces???
#Keep doing rand range until you hit a spot where list is == ' '
    O = "O"
    moveB = randrange(1,10)
    while space[moveB] != ' ':
        moveB = randrange(1,10)
    space[moveB] = O
    print("-------")
    print("|" + space[1] + "|" + space[2] + "|" + space[3] + "|")
    print("-------")
    print("|" + space[4] + "|" + space[5] + "|" + space[6] + "|")
    print("-------")
    print("|" + space[7] + "|" + space[8] + "|" + space[9] +"|")
    print("-------\n")
    return space


if __name__ == '__main__':
    main()
