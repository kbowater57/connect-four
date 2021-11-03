#include <vector>
#include <string>
#include <iostream>

void printBoard(std::vector<std::vector<std::string> > board)
{
    for (int i = board.size() - 1; i > -1 ; --i)
    {
        std::cout << "|";
        for (int j = 0 ; j < board[0].size() ; ++j)
        {
            std::cout << " " << board[i][j] << " |";
        }
        std::cout << "\n";
    }
        
}

int findCorrectRow(std::vector<std::vector<std::string> > board, int col)
{
    for (int row = 0 ; row < board.size() ; ++row)
    {
        if(board[row][col] == " "){
            return row;
        }
    }
    return -1;
}

bool checkInputValid(std::vector<std::vector<std::string> > board, int col)
{
    // first check that the column exists
    bool inputValid = (col > -1 && col < 8);
    if(!inputValid)
    {
        std::cout << "That column doesn't exist. Try again. \n";
        return inputValid;
    }

    // now check column isn't full
    inputValid = (board[board.size() - 1][col] == " ");
    if(!inputValid)
        std::cout << "That column is full. Try again. \n\n";

    return inputValid;
}


 int getMove(std::vector<std::vector<std::string> > board, std::string piece_type)
 {
    bool inputValid = false;
    int selected_col;
     while(inputValid == false)
     {
        std::cout << "In which column would you like to place a piece? \n";
        std::cin >> selected_col;
        --selected_col;
        inputValid = checkInputValid(board, selected_col);
     }
     return selected_col;
    
}

std::vector<std::vector<std::string> > updateBoard(std::vector<std::vector<std::string> > board, int col, std::string piece)
{
    int row = findCorrectRow(board, col);
    board[row][col] = piece;
    return board;
}

bool checkRowVictory(std::vector<std::vector<std::string> > board, std::string piece_type){
    int win_counter = 0;
    for( int i = 0 ; i < board.size() ; ++i)
    {
        for( int j = 0 ; j < board[0].size() ; ++j)
        {
            if(board[i][j] == piece_type)
            {
                ++win_counter;
                if(win_counter == 4)
                {
                    std::cout << "row win\n";
                    return true;
                }
            }
            else
                win_counter = 0;
        
        }
    }
    return false;
}

bool checkColVictory(std::vector<std::vector<std::string> > board, std::string piece_type)
{
    int win_counter = 0;
    for( int j = 0 ; j < board[0].size() ; ++j)
    {
        for( int i = 0 ; i < board.size() ; ++i)
        {
            if(board[i][j] == piece_type)
            {
                ++win_counter;
                if(win_counter == 4)
                {
                    std::cout << "col win \n";
                    return true;
                }
            }
            else
                win_counter = 0;
        
        }
    }
    return false;
}

bool checkInBounds(int i, int j, std::vector<std::vector<std::string> > board)
{
    if(i < 0 || i > board.size() - 1 || j < 0 or j > board[0].size() - 1)
        return false;
    return true;
}

bool checkDiagonalVictory(std::vector<std::vector<std::string> > board, std::string piece_type)
{
    int win_counter = 0;
    for( int i = 0 ; i < board.size() ; ++i)
    {
        for( int j = 0 ; j < board[0].size() ; ++j)
        {
            if( board[i][j] == piece_type)
            {
                // first check diagonal left up
                ++win_counter;
                while(win_counter < 4)
                {
                    if(checkInBounds(i + win_counter, j - win_counter,board))
                    {
                        if( board[i + win_counter][j - win_counter] == piece_type)
                        {
                            ++win_counter;
                            std::cout << "Checking square (" << i + win_counter << ", " << j - win_counter << "). Win counter = " << win_counter << "\n"; 
                        }
                        else
                        {
                            win_counter = 0;
                            break;
                        }
                    }
                    else
                    {
                        win_counter = 0;
                        break;
                    }
                }
                if(win_counter == 4)
                {
                    std::cout << "diagonal left up win \n";
                    return true;
                }


                
                // now check diagonal right up
                win_counter = 1;
                while(win_counter < 4)
                {
                    if( checkInBounds(i + win_counter, j + win_counter, board))
                    {
                        if( board[i + win_counter][j + win_counter] == piece_type)
                            ++win_counter;
                        else
                        {
                            win_counter = 0;
                            break;
                        }
                    }
                    else
                    {
                        win_counter = 0;
                        break;
                    }
                }
                if(win_counter == 4)
                {
                    std::cout << "diagonal right up win \n";
                    return true;
                }
            }
            else
                win_counter = 0;
        
        }
    }
    return false;
    
}

bool checkVictory(std::vector<std::vector<std::string> > board, std::string piece_type)
{
    return checkRowVictory(board, piece_type) || checkColVictory(board, piece_type) || checkDiagonalVictory(board, piece_type);
}



int main()
{
    std::vector<std::vector<std::string> > board(6, std::vector<std::string>(7, " "));
    std::string current_piece = "O";
    int turn = 1;
    while(true){

        // print board
        printBoard(board);

        // get a valid move from the user
        int col = getMove(board, current_piece);
    
        // place it
        board = updateBoard(board, col, current_piece);

        // // check for win, and display win message + board if win
        if(checkVictory(board, current_piece))
        {
            printBoard(board);
            std::cout << "Congratulations! You won! \n";
            break;
        }

        if(current_piece == "O")
            current_piece = "X";
        else
            current_piece = "O";

        turn++;
    }
   return 0;
}
