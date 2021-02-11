#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::vector<int>> ReadBoardFile ( std::string boardPath )
{
// readBoardFile function supports the path of the file as argument, opens it, processes it and
// returns a 2D Vector denoting a board.

    std::vector<std::vector<int>> board;
    // Creating an empty board inform of 2D-Vector to be read from file.

    std::ifstream boardFile;
    // File handler for opening a file.

    std::string row;
    // Initializing a new line to be read from the board file.

    boardFile.open( boardPath );
    // Opens the board file and process the file till it contains the lines. During the process, it
    // initialises the board.

    if( boardFile )
    {
    // Checks if the file exists.
        while(getline(boardFile, row))
        // Fetches a line from the file
        {
            std::cout<<row<<std::endl;
        }
    }
}

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
    std::string boardPath = "/home/kshitizsaini113/Git-Repo/RoutePlanner-with-OpenStreetMap/1.board";

    std::vector<std::vector<int>> board = ReadBoardFile( boardPath );

//    PrintBoard(board);
//    // Debugging by printing the board from PrintBoard function.

    return 0;
}