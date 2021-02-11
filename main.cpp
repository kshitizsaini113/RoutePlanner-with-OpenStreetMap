#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::abs;
using std::ifstream;
using std::istringstream;

enum class State
{
// Creating an enumerated datatype for creating a better access and make our program more readable.
// kEmpty denotes empty state
// kObstacle denotes that the path has some obstacle and can't be taken
// kClosed means that the path is already visited
    kEmpty,
    kObstacle
};

vector<vector<State>> ReadBoardFile ( string boardPath );
void PrintBoard( vector<vector<State>> board );
vector<State> ParseLine( string row );
vector<vector<State>> Search(vector<vector<State>> board, int initial[2], int final[2]);
int Heuristic(int x1, int y1, int x2, int y2);
// Defining functions first to make our initialization first.

vector<State> ParseLine( string rowString )
{
// parseLine function accepts a string as it's parameter and parses the line read from the file to
// extract the data from the file, store them into variable, converts them to the enumerated datatype
// and stores the enumerated data type to vector and returns it.

    istringstream my_stream(rowString);
    // Creates an object of istringstream class which is used to process the string.

    char c;
    int n;
    vector<State> rowVector;
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

vector<vector<State>> ReadBoardFile ( string boardPath )
{
// readBoardFile function supports the path of the file as argument, opens it, processes it and
// returns a 2D Vector denoting a board.

    vector<vector<State>> board;
    // Creating an empty board inform of 2D-Vector to be read from file.

    ifstream boardFile;
    // File handler for opening a file.

    string row;
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
            vector<State> row_n = ParseLine( row );

            board.push_back(row_n);
        }
    }
    else
    {
        // If no file is found, dumps the error on the standard error and closes the program.
        cerr<<"File not found"<<endl;
        exit(0);
    }

    return board;
    // Returns the board that is parsed from the file.
}

string CellString( State element )
{
// CellString function created to parse the value of enumerated datatype and returns the character
// encoding for the argument provided.
    switch( element )
    {
        case State::kObstacle:
            return "⛰️   ";
        default:
            return "0   ";
    }
}

void PrintBoard( vector<vector<State>> board )
{
// Takes the board as the argument for the printBoard function  and prints the board.

    cout<<endl;
    // Prints a new-line to make the formatting better.

    for( auto row: board )
    {
    // Access the rows from the board.
        for( auto element: row )
        {
        // Access the element from a particular row.
            cout<<CellString(element);
            // Prints the element of each row.
        }
        cout<<endl;
        // Prints a new line to access the data of a row in a single line.
    }
}

vector<vector<State>> Search(vector<vector<State>> board, int initial[2], int final[2])
{
    cout<<"No path found";

    return vector<vector<State>>{};
}

int Heuristic(int x1, int y1, int x2, int y2)
{
    return (abs( x2 - x1 ) + abs(y2 - y1));
}

#include "test.cpp"

int main()
{
    string boardPath = "/home/kshitizsaini113/Git-Repo/RoutePlanner-with-OpenStreetMap/1.board";

    vector<vector<State>> board = ReadBoardFile( boardPath );

    PrintBoard(board);
    // Debugging by printing the board from PrintBoard function.

    TestHeuristic();

    return 0;
}