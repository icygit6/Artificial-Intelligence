#include <iostream>
#include <string>
using namespace std;

int cflip(const string& board, int color, const string& grid, int dir) 
{
    char player = (color == 1) ? 'X' : 'O';
    char opp = (color == 1) ? 'O' : 'X';
    
    int row = grid[0] - 'A';
    int col = grid[1] - 'a';

    int dr[8] = {-1, -1,  0, 1, 1,  1,  0, -1};
    int dc[8] = { 0,  1,  1, 1, 0, -1, -1, -1};

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
            return (count > 0) ? count : 0;
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

string flip(const string& board, int color, const string& grid) 
{
    string newb = board;
    char player = (color == 1) ? 'X' : 'O';

    int row = grid[0] - 'A';
    int col = grid[1] - 'a';

    int dr[8] = {-1, -1,  0, 1, 1,  1,  0, -1};
    int dc[8] = { 0,  1,  1, 1, 0, -1, -1, -1};

    // Place the player's piece
    newb[row * 6 + col] = player;

    for (int dir = 0; dir < 8; dir++) 
    {
        int count = cflip(board, color, grid, dir);
        int r = row + dr[dir];
        int c = col + dc[dir];

        while (count-- > 0) 
        {
            newb[r * 6 + c] = player;
            r += dr[dir];
            c += dc[dir];
        }
    }

    return newb;
}

int main() 
{
    int tcase;
    cin >> tcase;

    for (int i = 0; i < tcase; i++) 
    {
        string board;
        cin >> board;

        int color;
        cin >> color;

        string grid;
        cin >> grid;

        cout << flip(board, color, grid) << endl;
    }

    return 0;
}
