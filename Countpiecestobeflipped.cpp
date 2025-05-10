#include <iostream>
#include <vector>
#include <string>
using namespace std;

int flip(const string& board, int color, const string& grid, int dir) 
{
    char player = (color == 1) ? 'X' : 'O';
    char opp = (color == 1) ? 'O' : 'X';
    
    int row = grid[0] - 'A'; // Convert row (A-F) to 0-5
    int col = grid[1] - 'a'; // Convert column (a-f) to 0-5
    
    // Directions: 0-up, 1-up-right, 2-right, 3-down-right, 4-down, 5-down-left, 6-left, 7-up-left
    int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    
    int r = row + dr[dir];
    int c = col + dc[dir];
    int count = 0;
    while (r >= 0 && r < 6 && c >= 0 && c < 6) 
    {
        char current = board[r * 6 + c];
        if (current == opp) 
        {
            count++;
        } 
        else if (current == player) 
        {
            return (count > 0) ? count: 0;
        }
        else 
        {
            return 0;
        }
        r += dr[dir];
        c += dc[dir];
    }
    return 0;
}

int main()
{
    int tcase;
    cin >> tcase;
    
    for (int i = 0; i < tcase; i++) 
    {
        string board;
        cin>> board;
        
        int color;
        cin >> color;
        
        string grid;
        cin>> grid;
        
        int dir;
        cin >> dir;
        
        cout << flip(board, color, grid, dir) << endl;
    }
    return 0;
}