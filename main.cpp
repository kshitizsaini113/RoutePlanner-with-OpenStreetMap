#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
// Importing the required headers for proper functionality of the project.

using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::abs;
using std::ifstream;
using std::istringstream;
using std::sort;
// Import specific functions to reduce the compilation and running time and to decrease the space used.

enum class State
{
// Creating an enumerated datatype for creating a better access and make our program more readable.
// kEmpty denotes empty state
// kObstacle denotes that the path has some obstacle and can't be taken
// kClosed means that the path is already visited

    kEmpty,
    kObstacle,
    kClosed,
    kPath,
    kStart,
    kFinish
};

const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
// Directional deltas specifies the position to which the route can be taken, e.g. the car can either
// move left, right, top or bottom, it cant traverse diagonally and it can only take one step at a time
// as the directional deltas specify.

vector<vector<State>> ReadBoardFile ( string boardPath );
void PrintBoard( vector<vector<State>> board );
vector<State> ParseLine( string row );
vector<vector<State>> Search(vector<vector<State>> board, int initial[2], int final[2]);
int Heuristic(int x1, int y1, int x2, int y2);
bool Compare(const vector<int> v1, const vector<int> v2);
bool CheckValidCell(int x, int y, vector<vector<State>> board);
string CellString( State element );
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openNodes, vector<vector<State>> &board);
void ExpandNeighbors(const vector<int> currentNode, int final[2], vector<vector<int>> &openNodes, vector<vector<State>> &board);
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
        case State::kPath:
            return "🚗   ";
        case State::kStart:
            return  "🚦   ";
        case State::kFinish:
            return "🏁   ";
        default:
            return "😨   ";
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

bool Compare(const vector<int> v1, const vector<int> v2)
{
// Function used to compare the f-values of two coordinates. Used in the CellSort function to compare
// the vectors using the sort function from algorithm.

    int cmp_f1 = v1[2] + v1[3];
    int cmp_f2 = v2[2] + v2[3];

    return cmp_f1 > cmp_f2;
}

int Heuristic(int x1, int y1, int x2, int y2)
{
// Took two points as the arguments and returns the manhattan distance of the two points. Manhattan
// distance is the distance between the two points where we can't move diagonally and the traffic or
// cost of move is equal for all the points.

    return (abs( x2 - x1 ) + abs(y2 - y1));
}

bool CheckValidCell(int x, int y, vector<vector<State>> board)
{
// Checks if the coordinates are present on the board and if the coordinates are present on the board,
// then validate if the coordinates are empty and can be used for traversal.

    bool is_x_on_grid = (x>=0 && x<board.size());
    bool is_y_on_grid = (y>=0 && y<board[0].size());
    // Checks if both the position lie on the board.

    if(is_x_on_grid && is_y_on_grid)
    {
        // If both the points are on grid, we check if the coordinates are available for traversal,
        // if they are available and not traversed first.
        return board[x][y] == State::kEmpty;
    }

    return false;
}

void CellSort(vector<vector<int>> *vec)
{
// Sorts the coordinates according to their cost of traversal using the Compare function that we have
// defined earlier, the sorting uses the sort function from algorithm header which accepts the beginning
// and ending address along with a comparison function.

    sort(vec->begin(), vec->end(), Compare);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openNodes, vector<vector<State>> &board)
{
// Add node to list of open nodes and mark it so that it can not be traversed again.

    openNodes.push_back(vector<int> {x, y, g, h});
    board[x][y] = State::kClosed;
}

void ExpandNeighbors(const vector<int> currentNode, int final[2], vector<vector<int>> &openNodes, vector<vector<State>> &board)
{
    int x1 = currentNode[0];
    int y1 = currentNode[1];
    int g1 = currentNode[2];
    // Fetches the information regarding the current node.

    for(int i=0; i<4; i++)
    {
        int x2 = x1 + delta[i][0];
        int y2 = y1 + delta[i][1];

        if( CheckValidCell(x2, y2, board) )
        {
            int g2 = g1 + 1;
            int h2 = Heuristic(x2, y2, final[0], final[1]);
            AddToOpen(x2, y2, g2, h2, openNodes, board);
        }
    }
}

vector<vector<State>> Search(vector<vector<State>> board, int initial[2], int final[2])
{
// Search function created for the creation of A* searching algorithm.Algorithm and the function
// calling for the A* search is done here after loading the data from the file onto the 2D Vector.

    vector<vector<int>> openNodes {};
    // Creating a vector of open nodes.

    int x1 = initial[0];
    int y1 = initial[1];
    int g1 = 0;
    int h = Heuristic(x1, y1, final[0], final[1]);
    AddToOpen(x1, y1, g1, h, openNodes, board);

    while( openNodes.size() > 0 )
    {
        CellSort(&openNodes);
        // Sorts the node according to their cost.

        auto current = openNodes.back();
        openNodes.pop_back();
        // Removes the last node from the list of open nodes as it is selected as current node.

        x1 = current[0];
        y1 = current[1];
        // Fetches the info about current node.

        board[x1][y1] = State::kPath;

        if(x1 == final[0] && y1 == final[1])
        {
        // Check if we have reached the final node.

            board[initial[0]][initial[1]] = State::kStart;
            board[final[0]][final[1]] = State::kFinish;
            // Mark the initial and final states.

            return board;
            // Returns the marked board
        }

        ExpandNeighbors(current, final, openNodes, board);
        // If the final destination is not found, then expand the search further to other nodes.
    }

    // If all the nodes have been explored, and no path is found, then end our search.

    cerr<<"No path found"<<endl;

    return vector<vector<State>>{};
}

//#include "test.cpp"

int main()
{
    int initial[2]{0, 0};
    int final[2]{4, 5};

    string boardPath = "/home/kshitizsaini113/Git-Repo/RoutePlanner-with-OpenStreetMap/1.board";

    vector<vector<State>> board = ReadBoardFile( boardPath );

    auto boardSolved = Search(board, initial, final);

    PrintBoard(boardSolved);
    // Debugging by printing the board from PrintBoard function.

    cout<<endl<<endl;

//    TestHeuristic();
//    TestAddToOpen();
//    TestCompare();
//    TestSearch();
//    TestCheckValidCell();
//    TestExpandNeighbors();

    return 0;
}