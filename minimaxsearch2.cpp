#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int cfp(const string& board, int pcolor, const string& grid, int dir)
{
    const int bsize = 6;
    char player = (pcolor == 1) ? 'X' : 'O';
    char opp = (pcolor == 1) ? 'O' : 'X';
    int row = grid[0] - 'A';
    int col = grid[1] - 'a';
    if (row < 0 || row >= bsize || col < 0 || col >= bsize) return 0;
    int pos = row * bsize + col;
    if (board[pos] != '+') return 0;
    const int dr[8] = { -1, -1,  0,  1, 1,  1,  0, -1 };
    const int dc[8] = { 0,  1,  1,  1, 0, -1, -1, -1 };
    int count = 0, r = row + dr[dir], c = col + dc[dir];
    while (r >= 0 && r < bsize && c >= 0 && c < bsize)
    {
        int currpos = r * bsize + c;
        char currpiece = board[currpos];
        if (currpiece == '+') return 0;
        if (currpiece == player) return count;
        if (currpiece == opp) count++;
        r += dr[dir]; c += dc[dir];
    }
    return 0;
}

string flip(const string& board, int pcolor, const string& grid)
{
    const int bsize = 6;
    string newb = board;
    int row = grid[0] - 'A';
    int col = grid[1] - 'a';
    int pos = row * bsize + col;
    char player = (pcolor == 1) ? 'X' : 'O';
    newb[pos] = player;
    const int dr[8] = { -1, -1,  0,  1, 1,  1,  0, -1 };
    const int dc[8] = { 0,  1,  1,  1, 0, -1, -1, -1 };
    for (int dir = 0; dir < 8; dir++)
    {
        int nflip = cfp(board, pcolor, grid, dir);
        if (nflip > 0)
        {
            int r = row, c = col;
            for (int i = 0; i < nflip; i++)
            {
                r += dr[dir];
                c += dc[dir];
                int flipPos = r * bsize + c;
                newb[flipPos] = player;
            }
        }
    }
    return newb;
}

int ccp(const string& board, int pcolor)
{
    char player = (pcolor == 1) ? 'X' : 'O';
    int count = 0;
    for (char c : board) if (c == player) count++;
    return count;
}

int heu(const string& board, int pcolor)
{
    int oppcolor = (pcolor == 1) ? 2 : 1;
    return ccp(board, pcolor) - ccp(board, oppcolor);
}

bool valmove(const string& board, int pcolor, const string& grid)
{
    for (int dir = 0; dir < 8; dir++)
        if (cfp(board, pcolor, grid, dir) > 0) return true;
    return false;
}

bool passTurn(const string& board, int pcolor)
{
    const int bsize = 6;
    for (int row = 0; row < bsize; row++)
        for (int col = 0; col < bsize; col++)
        {
            int pos = row * bsize + col;
            if (board[pos] == '+')
            {
                string grid = "";
                grid += static_cast<char>('A' + row);
                grid += static_cast<char>('a' + col);
                if (valmove(board, pcolor, grid)) return false;
            }
        }
    return true;
}

bool go(const string& board)
{
    return passTurn(board, 1) && passTurn(board, 2);
}

vector<string> getvalmove(const string& board, int pcolor)
{
    const int bsize = 6;
    vector<string> valid;
    for (int row = 0; row < bsize; row++)
        for (int col = 0; col < bsize; col++)
        {
            int pos = row * bsize + col;
            if (board[pos] == '+')
            {
                string grid = "";
                grid += static_cast<char>('A' + row);
                grid += static_cast<char>('a' + col);
                if (valmove(board, pcolor, grid)) valid.push_back(grid);
            }
        }
    return valid;
}

int minimax(const string& board, int pcolor, int depth, bool maxplayer, int alpha, int beta)
{
    int currEvalColor = maxplayer ? pcolor : (pcolor == 1 ? 2 : 1);
    if (depth == 0 || go(board)) return heu(board, currEvalColor);
    int currplayercolor = maxplayer ? pcolor : (pcolor == 1 ? 2 : 1);
    if (passTurn(board, currplayercolor)) return minimax(board, pcolor, depth - 1, !maxplayer, alpha, beta);
    vector<string> valid = getvalmove(board, currplayercolor);
    if (maxplayer)
    {
        int maxs = numeric_limits<int>::min();
        for (const string& move : valid)
        {
            string newb = flip(board, currplayercolor, move);
            int score = minimax(newb, pcolor, depth - 1, false, alpha, beta);
            maxs = max(maxs, score);
            alpha = max(alpha, score);
            if (beta <= alpha) break;
        }
        return maxs;
    }
    else
    {
        int mins = numeric_limits<int>::max();
        for (const string& move : valid)
        {
            string newb = flip(board, currplayercolor, move);
            int score = minimax(newb, pcolor, depth - 1, true, alpha, beta);
            mins = min(mins, score);
            beta = min(beta, score);
            if (beta <= alpha) break;
        }
        return mins;
    }
}

void printMoveScores(const string& board, int pcolor, int depth)
{
    vector<string> valid = getvalmove(board, pcolor);
    sort(valid.begin(), valid.end());

    string bestMove = "";
    int bestScore = numeric_limits<int>::min();

    for (const string& move : valid)
    {
        string newb = flip(board, pcolor, move);
        int score = minimax(newb, pcolor, depth - 1, false, numeric_limits<int>::min(), numeric_limits<int>::max());
        cout << move << " " << score << endl;

        if (score > bestScore || bestMove == "")
        {
            bestScore = score;
            bestMove = move;
        }
    }

    if (!bestMove.empty())
    {
        cout << "[" << bestMove << "]" << endl;
    }
}


int main()
{
    int in;
    cin >> in;
    for (int i = 0; i < in; i++)
    {
        string board;
        int pcolor, depth;
        cin >> board >> pcolor >> depth;
        printMoveScores(board, pcolor, depth);
    }
    return 0;
}
