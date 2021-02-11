#include <iostream>
#include <vector>

void PrintBoard( std::vector<std::vector<int>> board )
{
// Takes the board as the argument for the printBoard function  and prints the board.

    std::cout<<std::endl;
    // Prints a new-line to make the formatting better.

    for( auto row: board )
    {
    // Access the rows from the board.
        for( auto element: row )
        {
        // Access the element from a particular row.
            std::cout<<element<<"  ";
            // Prints the element of each row.
        }
        std::cout<<std::endl;
        // Prints a new line to access the data of a row in a single line.
    }
}

int main()
{
    std::vector<std::vector<int>> board = {{0, 1, 0, 0, 0, 0},
                                           {0, 1, 0, 0, 0, 0},
                                           {0, 1, 0, 0, 0, 0},
                                           {0, 1, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 1, 0}};
    // Creating a board in the form of vector.

    PrintBoard(board);
    // Debugging by printing the board from PrintBoard function.

    return 0;
}