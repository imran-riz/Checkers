#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include <Windows.h>

char Board[8][8] ;

struct Moves            // a structure to store details of all the possible moves the computer can make
{
    int row ;
    int column ;
    int numOfPcs ;      // stores the number of pieces the piece is gonna jump over
    char diagonal ;     // a 'r' for a simple move in right diagonal and a 'l' in the left. A 'R' for a jump in the right diagonal and 'L' in the left
    char direction ;    // an 'F' for forwards and 'B' for backwards
}Moves[100] ;

int rowMax = 8 ;
int colMax = 8 ;
int Xpieces = 12 ;
int Opieces = 12 ;
int moves ;             // keeps count of the possible moves the computer can perform

void initialize()
{
    int row, col ;

    // fill array with blanks
    for(row = 0 ; row < rowMax ; row++)
    {
        for(col = 0 ; col < colMax ; col++)
        {
            Board[row][col] = ' ' ;
        }
    }

    // initialize Os
    row = 0 ;
    while(row < 3)
    {
        if(row != 1)        
            col = 1 ;        
        else        
            col = 0 ;

        while(col < colMax)
        {
            Board[row][col] = 'o' ;
            col+=2 ;
        }

        row++ ;
    }

    // initialize Xs
    row = 5 ;
    while(row < rowMax)
    {
        if(row != 6)
            col = 0 ;
        else
            col = 1 ;

        while(col < colMax)
        {
            Board[row][col] = 'x' ;
            col+=2 ;
        }

        row++ ;
    }
}


void initializeStruct()
{
    for(int index = 0 ; index < 100 ; index++)
    {
        Moves[index].row = '\0' ;
        Moves[index].column = '\0' ;
        Moves[index].diagonal = '\0' ;
        Moves[index].direction = '\0' ;
        Moves[index].numOfPcs = 0 ;
    }
}

void dispBoard()
{
    system("cls") ;
    printf("\n\t\t\t\t   C H E C K E R S\n") ;

    int row, col ;

    printf("\n\n\n\t\t\t    1   2   3   4   5   6   7   8") ;
    for(row = 0 ; row < rowMax ; row++)
    {
        printf("\n\t\t\t  ---------------------------------\n\t\t\t") ;

        for(col = 0 ; col < colMax ; col++)
        {
            if(col == 0) printf("%d | ", row+1) ;
            printf("%c | ", Board[row][col]) ;
        }

        if(row == 1)
            printf("\tX pieces : %d", Xpieces) ;
        else if(row == 2)
            printf("\tO pieces : %d", Opieces) ;
    }

    printf("\n\t\t\t  ---------------------------------\n") ;
}


void dispAllMoves()         // function to display all moves the computer can perform
{
    int index = 0 ;

    printf("\n\n Pieces that can move");

    while(index < moves)
    {
        printf("\n(%d, %d)  diagonal : %c  direction : %c  numOfPcs : %d", (Moves[index].row)+1, (Moves[index].column)+1, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
        index+=1 ;
    }
}


int placePiece(int fromRow, int fromCol, char piece)        // returns a 1 if the user places the selected piece in a new location, else a 0
{
    dispBoard() ;

    int rowNum, colNum ;
    bool valid = false ;        

    printf("\nWhere do you wish to place this piece(row %d, column %d)?", fromRow+1, fromCol+1) ;
    while(!valid)
    {
        printf("\nEnter the row number : ") ;
        scanf("%d", &rowNum) ;
        printf("Enter the column number : ") ;
        scanf("%d", &colNum) ;

        rowNum-- ;
        colNum-- ;

        if(colNum == fromCol && rowNum == fromRow)      // check if the user returns the selected piece to its original location
            return 0 ;

        if(Board[rowNum][colNum] != ' ' || rowNum < 0 || rowNum > rowMax-1 || colNum < 0 || colNum > colMax-1 || rowNum == fromRow || colNum == fromCol)
        {
            valid = false ;
        }
        else if(piece == 'x' && rowNum > fromRow)
        {
            valid = false ;
        }
        else if(rowNum <= fromRow-1)    // this part of the IF statement applies to both men and Kings of the user's
        {
            if(rowNum == fromRow-1 && (colNum == fromCol+1 || colNum == fromCol-1))     // first check if it's merely a move in left or right diagonal
            {
                valid = true ;
            }                
            else if(colNum > fromCol+1)     // check if the user is tryna jump in the user's right diagonal
            {
                if(Board[fromRow-1][fromCol+1] == 'o' || Board[fromRow-1][fromCol+1] == 'O')    // check if the  user is attempting a jump
                {
                    if(rowNum == fromRow-2 && colNum == fromCol+2)
                    {
                        Board[fromRow-1][fromCol+1] = ' ' ;
                        Opieces-- ;
                        valid = true ;
                    }
                    else if(Board[fromRow-2][fromCol+2] == ' ')
                    {
                        if(Board[fromRow-3][fromCol+3] == 'o' || Board[fromRow-3][fromCol+3] == 'O')
                        {
                            if(rowNum == fromRow-4 && colNum == fromCol+4)
                            {
                                Board[fromRow-1][fromCol+1] = ' ' ;
                                Board[fromRow-3][fromCol+3] = ' ' ;
                                Opieces-=2 ;
                                valid = true ;
                            }
                            else if(Board[fromRow-4][fromCol+4] == ' ')
                            {
                                if(Board[fromRow-5][fromCol+5] == 'o' || Board[fromRow-5][fromCol+5] == 'O')
                                {
                                    if(rowNum == fromRow-6 && colNum == fromCol+6)
                                    {
                                        Board[fromRow-1][fromCol+1] = ' ' ;
                                        Board[fromRow-3][fromCol+3] = ' ' ;
                                        Board[fromRow-5][fromCol+5] = ' ' ;
                                        Opieces-=3 ;
                                        valid = true ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(colNum < fromCol-1)         // check if the user is tryna make a move in the user's left diagonal
            {
                if(Board[fromRow-1][fromCol-1] == 'o' || Board[fromRow-1][fromCol-1] == 'O')        // check if the user is attempting a jump in the left diagonal
                {
                    if(rowNum == fromRow-2 && colNum == fromCol-2)
                    {
                        Board[fromRow-1][fromCol-1] = ' ' ;
                        Opieces-- ;
                        valid = true ;
                    }
                    else if(Board[fromRow-2][fromCol-2] == ' ')
                    {
                        if(Board[fromRow-3][fromCol-3] == 'o' || Board[fromRow-3][fromCol-3] == 'O')
                        {
                            if(rowNum == fromRow-4 && colNum == fromCol-4)
                            {
                                Board[fromRow-1][fromCol-1] = ' ' ;
                                Board[fromRow-3][fromCol-3] = ' ' ;
                                Opieces-=2 ;
                                valid = true ;
                            }
                            else if(Board[fromRow-4][colNum-4] == ' ')
                            {
                                if(Board[fromRow-3][fromCol-5] == 'o' || Board[fromRow-3][fromCol-5] == 'O')
                                {
                                    if(rowNum == fromRow-6 && colNum == fromCol-6)
                                    {
                                        Board[fromRow-1][fromCol-1] = ' ' ;
                                        Board[fromRow-3][fromCol-3] = ' ' ;
                                        Board[fromRow-5][fromCol-5] = ' ' ;
                                        Opieces-=3 ;
                                        valid = true ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(piece == 'X' && rowNum >= fromRow)
        {
            if(rowNum == fromRow+1 && (colNum == fromCol-1 || colNum == fromCol+1))     // first check if its merely a move in right or left diagonal
            {
                valid = true ;
            }
            else            // check if the user is attempting to perform a jump
            {   
                if(colNum > fromCol+1)        // a jump in the user's right diagonal
                {
                    if(Board[fromRow+1][fromCol+1] == 'o' || Board[fromRow+1][fromCol+1] == 'O')
                    {
                        if(rowNum == fromRow+2 && colNum == fromCol+2)
                        {
                            Board[fromRow+1][fromCol+1] = ' ' ;
                            Opieces-- ;
                            valid = true ;
                        }
                        else if(Board[fromRow+2][fromCol+2] == ' ')
                        {
                            if(Board[fromRow+3][fromCol+3] == 'o' || Board[fromRow+3][fromCol+3] == 'O')
                            {
                                if(rowNum == fromRow+4 && colNum == fromCol+4)
                                {
                                    Board[fromRow+1][fromCol+1] = ' ' ;
                                    Board[fromRow+3][fromCol+3] = ' ' ;
                                    Opieces-=2 ;
                                    valid = true ;
                                }
                                else if(Board[fromRow+4][fromCol+4] == ' ')
                                {
                                    if(Board[fromRow+5][fromCol+5] == 'o' || Board[fromRow+5][fromCol+5] == 'O')
                                    {
                                        if(rowNum == fromRow+6 && colNum == fromCol+6)
                                        {
                                            Board[fromRow+1][fromCol+1] = ' ' ;
                                            Board[fromRow+3][fromCol+3] = ' ' ;
                                            Board[fromRow+5][fromCol+5] = ' ' ;
                                            Opieces-=3 ;
                                            valid = true ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else if(colNum < fromCol-1)       // a jump in the user's left diagonal
                {
                    if(Board[fromRow+1][fromCol-1] == 'o' || Board[fromRow+1][fromCol-1] == 'O')
                    {
                        if(rowNum == fromRow+2 && colNum == fromCol-2)
                        {
                            Board[fromRow+1][fromCol-1] = ' ' ;
                            Opieces-- ;
                            valid = true ;
                        }
                        else if(Board[fromRow+2][fromCol-2] == ' ')
                        {
                            if(Board[fromRow+3][fromCol-3] == 'o' || Board[fromRow+3][fromCol-3] == 'O')
                            {
                                if(rowNum == fromRow+4 && colNum == fromCol-4)
                                {
                                    Board[fromRow+1][fromCol-1] = ' ' ;
                                    Board[fromRow+3][fromCol-3] = ' ' ;
                                    Opieces-=2 ;
                                    valid = true ;
                                }
                                else if(Board[fromRow+4][fromCol-4] == ' ')
                                {
                                    if(Board[fromRow+5][fromCol-5] == 'o' || Board[fromRow+5][fromCol-5] == 'O')
                                    {
                                        if(rowNum == fromRow+6 && colNum == fromCol-6)
                                        {
                                            Board[fromRow+1][fromCol-1] = ' ' ;
                                            Board[fromRow+3][fromCol-3] = ' ' ;
                                            Board[fromRow+5][fromCol-5] = ' ' ;
                                            Opieces-=3 ;
                                            valid = true ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if(!valid) 
            printf("\nINVALID MOVE! Try again! \n") ;
    }

    if(rowNum == 0) piece = 'X' ;        // a man becomes a King once he reaches the opposite end

    Board[rowNum][colNum] = piece ;    
    return 1 ;
}


void getMove()
{
        
    int rowNum, colNum ;    
    char piece ;

    while(1)        // loop runs until the user places a selected piece in a new location
    {
        dispBoard() ;
        bool valid = false ;

        printf("\nSelect A Piece(X)") ;

        while(!valid)
        {
            printf("\n Enter the row number : ") ;
            scanf("%d", &rowNum) ;
            printf(" Enter the column number : ") ;
            scanf("%d", &colNum) ;

            rowNum-- ;
            colNum-- ;
            piece = Board[rowNum][colNum] ;

            if(rowNum > 7 || rowNum < 0 || colNum > 7 || colNum < 0 || (Board[rowNum][colNum] != 'x' && Board[rowNum][colNum] != 'X'))
                printf("\n\t\tINVALID ENTRY! Try again!\n") ;
            else
                valid = true ;
        }        

        Board[rowNum][colNum] = ' ' ;

        if(placePiece(rowNum, colNum, piece) == 1)
            break ;

        Board[rowNum][colNum] = piece ;
    }

    dispBoard() ;
}


void performJump(int row, int col, char diagl, char dir, int num)       // the num variable holds the number of pieces the computer's piece is gonna jump over
{
    char piece = Board[row][col] ;
    Board[row][col] = ' ' ;

    if(dir == 'F')
    {
        if(row+(num*2) == rowMax-1)
            piece = 'O' ;
    }

    if(diagl == 'L')
    {
        if(dir == 'F')
        {
            Board[row+1][col+1] = ' ' ;

            if(num <= 3 && num > 1)
                Board[row+3][col+3] = ' ' ;
            if(num == 3)
                Board[row+5][col+5] = ' ' ;

            if(num == 1)
                Board[row+2][col+2] = piece ;
            else if(num == 2)
                Board[row+4][col+4] = piece ;
            else
                Board[row+6][col+6] = piece ;
        }
        else if(dir == 'B')
        {
            Board[row-1][col-1] = ' ' ;

            if(num <= 3 && num > 1)
                Board[row-3][col-3] = ' ' ;
            if(num == 3)
                Board[row-5][col-5] = ' ' ;

            if(num == 1)
                Board[row-2][col-2] = piece ;
            else if(num == 2)
                Board[row-4][col-4] = piece ;
            else
                Board[row-6][col-6] = piece ;            
        }
    }
    else if(diagl == 'R')
    {
        if(dir == 'F')
        {
            Board[row+1][col-1] = ' ' ;

            if(num <= 3 && num > 1)
                Board[row+3][col-3] = ' ' ;
            if(num == 3)
                Board[row+5][col-5] = ' ' ;

            if(num == 1)
                Board[row+2][col-2] = piece ;
            else if(num == 2)
                Board[row+4][col-4] = piece ;
            else
                Board[row+6][col-6] = piece ;
        }
        else if(dir == 'B')
        {
            Board[row-1][col+1] = ' ' ;

            if(num <= 3 && num > 1)
                Board[row-3][col+3] = ' ' ;
            if(num == 3)
                Board[row-5][col+5] = ' ' ;

            if(num == 1)
                Board[row-2][col+2] = piece ;
            else if(num == 2)
                Board[row-4][col+4] = piece ;
            else
                Board[row-6][col+6] = piece ;            
        }
    }

    Xpieces = Xpieces - num ;    
}


int canJump(int row, int col, char diagl, char dir)      // function to check if an O piece can perform a jump
{
    int num = 0 ;       // stores the number of jumps(1, 2 or 3)

    if(dir == 'F')
    {
        if(row+2 < rowMax)
        {
            if(diagl == 'L')
            {
                if(col+2 < colMax)
                {
                    if((Board[row+1][col+1] == 'x' || Board[row+1][col+1] == 'X') && Board[row+2][col+2] == ' ')
                    {
                        num++ ;

                        if(row+4 < rowMax && col+4 < colMax)
                        {
                            if((Board[row+3][col+3] == 'x' || Board[row+3][col+3] == 'X') && Board[row+4][col+4] == ' ')
                            {
                                num++ ;

                                if(row+6 < rowMax && col+6 < colMax)
                                {
                                    if((Board[row+5][col+5] == 'x' || Board[row+5][col+5] == 'X') && Board[row+6][col+6] == ' ')
                                        num++ ;
                                }
                            }
                        }
                    }
                }
            }
            else if(diagl == 'R')
            {
                if(col-2 >= 0)
                {
                    if((Board[row+1][col-1] == 'x' || Board[row+1][col-1] == 'X') && Board[row+2][col-2] == ' ')
                    {
                        num++ ;

                        if(row+4 < rowMax && col-4 >= 0)
                        {
                            if((Board[row+3][col-3] == 'x' || Board[row+3][col-3] == 'X') && Board[row+4][col-4] == ' ')
                            {
                                num++ ;

                                if(row+6 < rowMax && col-6 >= 0)
                                {
                                    if((Board[row+5][col-5] == 'x' || Board[row+5][col-5] == 'X') && Board[row+6][col-6] == ' ')
                                        num++ ;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if(dir == 'B')
    {
        if(row-2 >= 0)
        {
            if(diagl == 'L')
            {
                if(col-2 >= 0)
                {
                    if((Board[row-1][col-1] == 'x' || Board[row-1][col-1] == 'X') && Board[row-2][col-2] == ' ')
                    {
                        num++ ;

                        if(row-4 >= 0 && col-4 >= 0)
                        {
                            if((Board[row-3][col-3] == 'x' || Board[row-3][col-3] == 'X') && Board[row-4][col-4] == ' ')
                            {
                                num++ ;

                                if(row-6 >= 0 && col-6 >= 0)
                                {
                                    if((Board[row-5][col-5] == 'x' || Board[row-5][col-5] == 'X') && Board[row-6][col-6] == ' ')
                                        num++ ;
                                }
                            }
                        }
                    }
                }
            }
            else if(diagl == 'R')
            {
                if(col+2 < colMax)
                {
                    if((Board[row-1][col+1] == 'x' || Board[row-1][col+1] == 'X') && Board[row-2][col+2] == ' ')
                    {
                        num++ ;

                        if(row-4 >= 0 && col+4 < colMax)
                        {
                            if((Board[row-3][col+3] == 'x' || Board[row-3][col+3] == 'X') && Board[row-4][col+4] == ' ')
                            {
                                num++ ;

                                if(row-6 >= 0 && col+6 < colMax)
                                {
                                    if((Board[row-5][col+5] == 'x' || Board[row-5][col+5] == 'X') && Board[row-6][col+6] == ' ')
                                        num++ ;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return num ;    // a 0 is returned meaning that a jump cannot be performed
}


void checkForJumps()            // function to check if any O piece can make any jumps. If so, then check if performing the jump is a safe move and make it if its safe
{
    int rowNum, colNum, num ;

    for(rowNum = rowMax-1 ; rowNum > -1 ; rowNum--)     // start counting from the last row
    {        
        for(colNum = 0 ; colNum <= colMax-1 ; colNum++)         // start counting from the first row
        {
            if(Board[rowNum][colNum] == 'o' || Board[rowNum][colNum] == 'O')       // first check for forward jumps for both men and kings
            {
                num = canJump(rowNum, colNum, 'L', 'F') ;
                if(num != 0)
                {
                    Moves[moves].row = rowNum ;
                    Moves[moves].column = colNum ;
                    Moves[moves].diagonal = 'L' ;
                    Moves[moves].direction = 'F' ;
                    Moves[moves].numOfPcs = num ;
                    moves++ ;
                }

                num = canJump(rowNum, colNum, 'R', 'F') ;
                if(num != 0)
                {
                    Moves[moves].row = rowNum ;
                    Moves[moves].column = colNum ;
                    Moves[moves].diagonal = 'R' ;
                    Moves[moves].direction = 'F' ;
                    Moves[moves].numOfPcs = num ;
                    moves++ ;
                }
            }
            
            if(Board[rowNum][colNum] == 'O')       // for a king check for a backward jump
            {
                num = canJump(rowNum, colNum, 'L', 'B') ;
                if(num != 0)
                {
                    Moves[moves].row = rowNum ;
                    Moves[moves].column = colNum ;
                    Moves[moves].diagonal = 'L' ;
                    Moves[moves].direction = 'B' ;
                    Moves[moves].numOfPcs = num ;
                    moves++ ;
                }

                num = canJump(rowNum, colNum, 'R', 'B') ;
                if(num != 0)
                {
                    Moves[moves].row = rowNum ;
                    Moves[moves].column = colNum ;
                    Moves[moves].diagonal = 'R' ;
                    Moves[moves].direction = 'B' ;
                    Moves[moves].numOfPcs = num ;
                    moves++ ;                    
                }
            }
        }        
    }
}


void findAllMoves()
{
    initializeStruct() ;
    moves = 0 ;
    int rowNum, colNum ;
    
    checkForJumps() ;           // first check if any jumps can be made

    for(rowNum = rowMax-1 ; rowNum > -1 ; rowNum--)     // start counting from the last row
    {
        for(colNum = 0 ; colNum < colMax ; colNum++)      // start counting from the first column
        {
            if(rowNum == rowMax-1 && colNum == 0)      // check square (8, 0)
            {
                if(Board[rowNum][colNum] == 'O')
                {
                    if(Board[rowNum-1][colNum+1] == ' ')
                    {
                        Moves[moves].row = rowNum ;
                        Moves[moves].column = colNum ;
                        Moves[moves].diagonal = 'l' ;
                        Moves[moves].direction = 'B' ;                        
                        moves++ ;
                    }
                }
            }
            else if(rowNum == rowMax-1 && colNum == colMax-1)       // check the square (8, 8)
            {
                if(Board[rowNum][colNum] == 'O')
                {
                    if(Board[rowNum-1][colNum-1] == ' ')
                    {
                        Moves[moves].row = rowNum ;
                        Moves[moves].column = colNum ;
                        Moves[moves].diagonal = 'r' ;
                        Moves[moves].direction = 'B' ;                        
                        moves++ ;
                    }
                }
            }
            else if(rowNum == 0 && colNum == 0)         // check square (1, 1)
            {
                if(Board[rowNum][colNum] == 'o' || Board[rowNum][colNum] == 'O')
                {
                    if(Board[rowNum+1][colNum+1] == ' ')
                    {
                        Moves[moves].row = rowNum ;
                        Moves[moves].column = colNum ;
                        Moves[moves].diagonal = 'l' ;
                        Moves[moves].direction = 'F' ;                        
                        moves++ ;
                    }
                }
            }
            else if(rowNum == 0 && colNum == colMax-1)      // check square (1, 8)
            {
                if(Board[rowNum][colNum] == 'o' || Board[rowNum][colNum] == 'O')
                {
                    if(Board[rowNum+1][colNum-1] == ' ')
                    {
                        Moves[moves].row = rowNum ;
                        Moves[moves].column = colNum ;
                        Moves[moves].diagonal = 'r' ;
                        Moves[moves].direction = 'F' ;                        
                        moves++ ;
                    }
                }
            }
            else
            {
                if(colNum == 0)     // check the first column
                {
                    if(Board[rowNum][colNum] == 'o' || Board[rowNum][colNum] == 'O')
                    {
                        if(Board[rowNum+1][colNum+1] == ' ')    // check if a simple move in the left diagonal(forwards) can be made
                        {
                            Moves[moves].row = rowNum ;
                            Moves[moves].column = colNum ;
                            Moves[moves].diagonal = 'l' ;
                            Moves[moves].direction = 'F' ;                            
                            moves++ ;
                        }
                    }

                    if(Board[rowNum][colNum] == 'O')
                    {
                        if(Board[rowNum-1][colNum+1] == ' ')
                        {
                            Moves[moves].row = rowNum ;
                            Moves[moves].column = colNum ;
                            Moves[moves].diagonal = 'l' ;
                            Moves[moves].direction = 'B' ;                            
                            moves++ ;
                        }
                    }
                }
                else if(colNum == colMax-1)     // check the last column
                {
                    if(Board[rowNum][colNum] == 'o' || Board[rowNum][colNum] == 'O')
                    {
                        if(Board[rowNum+1][colNum-1] == ' ')    // check if a simple move in the right diagonal(forwards) can be made
                        {
                            Moves[moves].row = rowNum ;
                            Moves[moves].column = colNum ;
                            Moves[moves].diagonal = 'r' ;
                            Moves[moves].direction = 'F' ;                            
                            moves++ ;
                        }
                    }

                    if(Board[rowNum][colNum] == 'O')
                    {
                        if(Board[rowNum-1][colNum-1] == ' ')
                        {
                            Moves[moves].row = rowNum ;
                            Moves[moves].column = colNum ;
                            Moves[moves].diagonal = 'r' ;
                            Moves[moves].direction = 'B' ;                            
                            moves++ ;
                        }
                    }
                }
                else
                {
                    if(Board[rowNum][colNum] == 'o' || Board[rowNum][colNum] == 'O')    // conditions in this IF statement apply to both men & kings
                    {
                        if(rowNum != rowMax-1 && Board[rowNum+1][colNum+1] == ' ')    // check if a simple move in the left diagonal(forwards) can be made
                        {
                            Moves[moves].row = rowNum ;
                            Moves[moves].column = colNum ;
                            Moves[moves].diagonal = 'l' ;
                            Moves[moves].direction = 'F' ;                            
                            moves++ ;
                        }

                        if(rowNum != rowMax-1 && Board[rowNum+1][colNum-1] == ' ')    // check if a simple move in the right diagonal(forwards) can be made
                        {
                            Moves[moves].row = rowNum ;
                            Moves[moves].column = colNum ;
                            Moves[moves].diagonal = 'r' ;
                            Moves[moves].direction = 'F' ;                            
                            moves++ ;
                        }
                    }
                }

                if(Board[rowNum][colNum] == 'O')        // conditions in this IF statement apply to kings only
                {
                    if(rowNum != 0 && Board[rowNum-1][colNum-1] == ' ')    // check if a simple move in the left diagonal(backwards) can be made
                    {
                        Moves[moves].row = rowNum ;
                        Moves[moves].column = colNum ;
                        Moves[moves].diagonal = 'l' ;
                        Moves[moves].direction = 'B' ;                        
                        moves++ ;
                    }

                    if(rowNum != 0 && Board[rowNum-1][colNum+1] == ' ')    // check if a simple move in the right diagonal(backwards) can be made
                    {
                        Moves[moves].row = rowNum ;
                        Moves[moves].column = colNum ;
                        Moves[moves].diagonal = 'r' ;
                        Moves[moves].direction = 'B' ;                        
                        moves++ ;
                    }
                }
            }
        }
    }
}


void makeMove()
{    
    findAllMoves() ;
//    dispAllMoves() ;

    int rowNum, colNum, newRow, newCol ;
    char piece ;    
    bool mustMove = false ;
    bool moveMade = false ;

    while(1)
    {        
        for(int index = 0 ; index < moves ; index++)
        {
            rowNum = Moves[index].row ;
            colNum = Moves[index].column ;
            piece = Board[rowNum][colNum] ;

            if(piece == 'O' && rowNum == rowMax-1 && Moves[index].diagonal != 'R' && Moves[index].diagonal != 'L')
            {
                printf("\n%d", mustMove) ;  // a 1 represenrs true and 0 a false

                if(mustMove)
                {
                    if(Moves[index].diagonal == 'l')
                    {
                        Board[rowNum][colNum] = ' ' ;
                        Board[rowNum-1][colNum-1] = piece ; 
                        moveMade = true ;
                    }
                    else if(Moves[index].diagonal == 'r')
                    {
                        Board[rowNum][colNum] = ' ' ;
                        Board[rowNum-1][colNum+1] = piece ; 
                        moveMade = true ;
                    }
                }
            }
            else
            {
                if(Moves[index].diagonal == 'R')          // for a jump in the right diagonal
                {
                    if(Moves[index].direction == 'F')
                    {
                        newRow = rowNum + (Moves[index].numOfPcs * 2) ;
                        newCol = colNum - (Moves[index].numOfPcs * 2) ;

                        if(newRow == rowMax-1 || newCol == 0 || mustMove == true)
                        {
                            performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                            moveMade = true ;
                        }
                        else
                        {
                            if((Board[newRow+1][newCol+1] != 'x' && Board[newRow+1][newCol+1] != 'X') && (Board[newRow+1][newCol-1] != 'x' && Board[newRow+1][newCol-1] != 'X'))
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                            else if(Board[newRow+1][newCol-1] == ' ' && Board[newRow+1][newCol+1] != ' ' && Board[newRow-1][newCol-1] != ' ')
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                        }
                    }
                    else if(Moves[index].direction == 'B')
                    {
                        newRow = rowNum - (Moves[index].numOfPcs * 2) ;
                        newCol = colNum + (Moves[index].numOfPcs * 2) ;

                        if(newRow == 0 || newCol == colMax-1 || mustMove == true)
                        {
                            performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                            moveMade = true ;
                        }
                        else
                        {
                            if((Board[newRow-1][newCol+1] != 'x' && Board[newRow-1][newCol+1] != 'X') && (Board[newRow-1][newCol-1] != 'x' && Board[newRow-1][newCol-1] != 'X'))
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                            else if(Board[newRow-1][newCol+1] == ' ' && Board[newRow-1][newCol-1] != ' ' && Board[newRow+1][newCol+1] != ' ')
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                        }
                    }
                }
                else if(Moves[index].diagonal == 'L')     // for a jump in the left diagonal
                {
                    if(Moves[index].direction == 'F')
                    {
                        newRow = rowNum + (Moves[index].numOfPcs * 2) ;
                        newCol = colNum + (Moves[index].numOfPcs * 2) ;

                        if(newRow == rowMax-1 || newCol == colMax-1 || mustMove == true) 
                        {
                            performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                            moveMade = true ;
                        }
                        else
                        {
                            if((Board[newRow+1][newCol+1] != 'x' && Board[newRow+1][newCol+1] != 'X') && (Board[newRow+1][newCol-1] != 'x' && Board[newRow+1][newCol-1] != 'X'))
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                            else if(Board[newRow+1][newCol+1] == ' ' && Board[newRow+1][newCol-1] != ' ' && Board[newRow-1][newCol+1] != ' ')
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                        }
                    }
                    else if(Moves[index].direction == 'B')
                    {
                        newRow = rowNum - (Moves[index].numOfPcs * 2) ;
                        newCol = colNum - (Moves[index].numOfPcs * 2) ;

                        if(newRow == 0 || newCol == 0 || mustMove == true)
                        {
                            performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                            moveMade = true ;
                        }
                        else
                        {
                            if((Board[newRow-1][newCol+1] != 'x' && Board[newRow-1][newCol+1] != 'X') && (Board[newRow-1][newCol-1] != 'x' && Board[newRow-1][newCol-1] != 'X'))
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                            else if(Board[newRow-1][newCol-1] == ' ' && Board[newRow-1][newCol+1] != ' ' && Board[newRow+1][newCol-1] != ' ')
                            {
                                performJump(rowNum, colNum, Moves[index].diagonal, Moves[index].direction, Moves[index].numOfPcs) ;
                                moveMade = true ;
                            }
                        }
                    }
                }
                else 
                {
                    if(Moves[index].direction == 'F' && rowNum+1 == rowMax-1)
                        piece = 'O' ;

                    if(Moves[index].diagonal == 'r')     // for a simple move thats in the right diagonal
                    {
                        if(Moves[index].direction == 'F')
                        {
                            newRow = rowNum + 1 ;
                            newCol = colNum - 1 ;

                            if(newRow == rowMax-1 || newCol == 0 || mustMove == true)
                            {
                                //printf("\n A") ;
                                Board[rowNum][colNum] = ' ' ;
                                Board[newRow][newCol] = piece ; 
                                moveMade = true ;
                            }
                            else
                            {
                                if((Board[newRow+1][newCol+1] != 'x' && Board[newRow+1][newCol+1] != 'X') && (Board[newRow+1][newCol-1] != 'x' && Board[newRow+1][newCol-1] != 'X'))
                                {
//                                   printf("\n B") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if(Board[newRow+1][newCol-1] == ' ' && Board[rowNum][colNum-2] != ' ' && Board[newRow+1][newCol+1] != ' ')
                                {
//                                    printf("\n C") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if((Board[newRow+1][newCol+1] != 'x' && Board[newRow+1][newCol+1] != 'X') && ((Board[newRow+1][newCol-1] == 'x' || Board[newRow+1][newCol-1] == 'X') && (colNum+1 <= colMax-1 && colNum-1 >= 0 && ((Board[rowNum-1][colNum+1] == 'o' || Board[rowNum-1][colNum+1] == 'O') || ((Board[rowNum-1][colNum-1] == 'o' || Board[rowNum-1][colNum-1] == 'O') && Board[rowNum+1][colNum+1] == ' ')))))
                                {
//                                    printf("\n D") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if((Board[newRow+1][newCol-1] != 'x' && Board[newRow+1][newCol-1] != 'X') && ((Board[newRow+1][newCol+1] == 'x' || Board[newRow+1][newCol+1] == 'X') && ((colNum-3 >= 0 && (Board[rowNum-1][colNum-3] == 'o' || Board[rowNum-1][colNum-3] == 'O') || ((Board[rowNum-1][colNum-1] == 'o' || Board[rowNum-1][colNum-1] == 'O') && Board[rowNum+1][colNum-3] == ' ')))))
                                {
//                                    printf("\n E") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                            }
                        }
                        else if(Moves[index].direction == 'B' && rowNum == rowMax-1)
                        {
                            newRow = rowNum - 1 ;
                            newCol = colNum + 1 ;

                            if(newRow == 0 || newCol == colMax-1 || mustMove == true)
                            {
//                                printf("\n F") ;
                                Board[rowNum][colNum] = ' ' ;
                                Board[newRow][newCol] = piece ; 
                                moveMade = true ;
                            }
                            else
                            {
                                if((Board[newRow-1][newCol+1] != 'x' && Board[newRow-1][newCol+1] != 'X') && (Board[newRow-1][newCol-1] != 'x' && Board[newRow-1][newCol-1] != 'X'))
                                {
//                                    printf("\n G") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if(Board[newRow-1][newCol+1] == ' ' && Board[rowNum][colNum+2] != ' ' && Board[rowNum-2][colNum] != ' ')
                                {
//                                    printf("\n H") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                            }
                        }
                    }
                    else if(Moves[index].diagonal == 'l')     // for a simple move thats in the left diagonal 
                    {
                        if(Moves[index].direction == 'F')
                        {
                            newRow = rowNum + 1 ;
                            newCol = colNum + 1 ;

                            if(newRow == rowMax-1 || newCol == colMax-1 || mustMove == true)
                            {
//                                printf("\n I") ;
                                Board[rowNum][colNum] = ' ' ;
                                Board[newRow][newCol] = piece ; 
                                moveMade = true ;
                            }
                            else
                            {
                                if((Board[newRow+1][newCol+1] != 'x' && Board[newRow+1][newCol+1] != 'X') && (Board[newRow+1][newCol-1] != 'x' && Board[newRow+1][newCol-1] != 'X'))
                                {
//                                    printf("\n J") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if(Board[newRow+1][newCol+1] == ' ' && Board[rowNum+2][colNum] != ' ' && Board[rowNum][colNum+2] != ' ')
                                {
//                                    printf("\n K") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if((Board[newRow+1][newCol-1] != 'x' && Board[newRow+1][newCol-1] != 'X') && (Board[newRow+1][newCol+1] == 'x' || Board[newRow+1][newCol+1] == 'X') && (rowNum-1 >= 0 && colNum-1 >= 0 && ((Board[rowNum-1][colNum-1] == 'o' || Board[rowNum-1][colNum-1] == 'O') || ((Board[rowNum-1][colNum+1] == 'o' || Board[rowNum-1][colNum+1] == 'O') && Board[rowNum+1][colNum-1] == ' '))))
                                {
//                                    printf("\n L") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if((Board[newRow+1][newCol+1] != 'x' && Board[newRow+1][newCol+1] != 'X') && ((Board[newRow+1][newCol-1] == 'x' || Board[newRow+1][newCol-1] == 'X') && (rowNum+3 <= rowMax-1 && ((Board[rowNum-1][colNum+3] == 'o' || Board[rowNum-1][colNum+3] == 'O') || ((Board[rowNum-1][colNum+1] == 'o' || Board[rowNum-1][colNum+1] ==  'O') && Board[rowNum+1][colNum+3] == ' ')))))
                                {
//                                    printf("\n M") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                            }
                        }
                        else if(Moves[index].direction == 'B' && rowNum != rowMax-1)
                        {
                            newRow = rowNum - 1 ;
                            newCol = colNum - 1 ;

                            if(newRow == 0 || newCol == 0 || mustMove == true)
                            {
//                                printf("\n N") ;
                                Board[rowNum][colNum] = ' ' ;
                                Board[newRow][newCol] = piece ; 
                                moveMade = true ;
                            }
                            else
                            {
                                if((Board[newRow+1][newCol+1] != 'x' && Board[newRow+1][newCol+1] != 'X') && (Board[newRow+1][newCol-1] != 'x' && Board[newRow+1][newCol-1] != 'X'))
                                {
//                                    printf("\n O") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                                else if(Board[newRow-1][newCol-1] == ' ' && Board[rowNum][colNum-2] != ' ' && Board[rowNum-2][colNum] != ' ')
                                {
//                                    printf("\n P") ;
                                    Board[rowNum][colNum] = ' ' ;
                                    Board[newRow][newCol] = piece ; 
                                    moveMade = true ;
                                }
                            }
                        }
                    }
                }

                if(moveMade)
                    break ;
            }
        }

        if(!moveMade)
            mustMove = true ;
        else 
            break ;
    }

    dispBoard() ;
}


int main(int argc, char const *argv[])
{
    system("cls") ;
    char choice = 'y' ;

    while(choice == 'y' || choice == 'Y')
    {
        initialize() ;

        while(1)
        { 
            getMove() ;
            Sleep(1000 * 2) ;       // put the computer to sleep for 2 seconds
            makeMove() ;

            if(Xpieces == 1 && Opieces == 1)                 // check for a draw
            {
                break ;
            }
            else if(Xpieces == 1 && Opieces > 1)
            {
                printf("\n\n\n\t\t\tG A M E  O V E R") ;
                printf("\n\t\t\tY O U  L O S E");
                break ;
            }
            else if(Opieces == 1 && Xpieces > 1)
            {
                printf("\n\n\n\t\t\tG A M E  O V E R") ;
                printf("\n\t\t\tY O U  W I N");
                break ;
            }
        }

        printf("\n\nReplay(Y/N)? ") ;
        scanf("\n%c", &choice) ;
    }

    system("cls") ;

    return 0;
}