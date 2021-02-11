#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

enum class State
{
// Creating an enumerated datatype for creating a better access and make our program more readable.
// kEmpty denotes empty state
// kObstacle denotes that the path has some obstacle and can't be taken
// kClosed means that the path is already visited
    kEmpty,
    kObstacle
};

std::vector<std::vector<State>> ReadBoardFile ( std::string boardPath );
void PrintBoard( std::vector<std::vector<int>> board );
std::vector<State> ParseLine( std::string row );

std::vector<State> ParseLine( std::string rowString )
{
// parseLine function accepts a string as it's parameter and parses the line readed from the file to
// extract the data from the file, store them into variable, converts them to the enumerated datatype
// and stores the enumerated data type to vector and returns it.

    std::istringstream my_stream(rowString);
    // Creates an object of istringstream class which is used to process the string.

    char c;
    int n;
    std::vector<State> rowVector;
    // Initialise the variables to be used to fetch the value from the string.

    while(my_stream >> n >> c && c ==',')
    {
        // Streams string till the string is non empty and is a combination of integer and a character,
        // further checks if the string ends with comma(,)
        if(n == 0)
        {
            // If element is zero, we mark it as empty element.
            rowVector.push_back(State::kEmpty);
        }
        else
        {
            // If element is non-zero we mark it as an obstacle.
            rowVector.push_back(State::kObstacle);
        }
    }

    return rowVector;
    // Returns a row in the form of vector after processing the input string.
}

std::vector<std::vector<State>> ReadBoardFile ( std::string boardPath )
{
// readBoardFile function supports the path of the file as argument, opens it, processes it and
// returns a 2D Vector denoting a board.

    std::vector<std::vector<State>> board;
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
            // Fetches a line from the file and parses it using the parseLine function. Finally, the
            // parsed values from the line are added on to the board.
        {
            std::vector<State> row_n = ParseLine( row );

            board.push_back(row_n);
        }
    }
    else
    {
        // If no file is found, dumps the error on the standard error and closes the program.
        std::cerr<<"File not found"<<std::endl;
        exit(0);
    }

    return board;
    // Returns the board that is parsed from the file.
}

std::string CellString( State element )
{
    switch( element )
    {
        case State::kObstacle:
            return "⛰️   ";
        default:
            return "0   ";
    }
}

void PrintBoard( std::vector<std::vector<State>> board )
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
            std::cout<<CellString(element);
            // Prints the element of each row.
        }
        std::cout<<std::endl;
        // Prints a new line to access the data of a row in a single line.
    }
}

int main()
{
    std::string boardPath = "/home/kshitizsaini113/Git-Repo/RoutePlanner-with-OpenStreetMap/1.board";

    std::vector<std::vector<State>> board = ReadBoardFile( boardPath );

    PrintBoard(board);
    // Debugging by printing the board from PrintBoard function.

    return 0;
}