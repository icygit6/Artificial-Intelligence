#include <iostream>
#include <string>
using namespace std;

int countcolor(const string& board, int color)
{
    char player = (color == 1) ? 'X' : 'O';
    int count = 0;

    for (char c : board)
    {
        if (c == player)
            count++;
    }
    return count;
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
        cout << countcolor(board, color) << endl;
    }
    return 0;
}
