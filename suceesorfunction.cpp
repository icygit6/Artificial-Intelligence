#include <iostream>
using namespace std;
int main()
 {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
     {
        string move;
        cin >> move;
        int mat[3][3];
        int dex = 0;
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                mat[i][j] = move[dex++] - '0';
            }
        }
        int x0 = -1, y0 = -1;
        for (int i = 0; i < 3; i++)
         {
            for (int j = 0; j < 3; j++)
             {
                if (mat[i][j] == 0)
                 {
                    x0 = i;
                    y0 = j;
                    break;
                }
            }
        }
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        string dir[] = {"up", "down", "left", "right"};
        int c = 0;
        string next[4];
        string flag[4];
        for (int i = 0; i < 4; i++) 
        {
            int x = x0 + dx[i];
            int y = y0 + dy[i];
            if (x >= 0 && x < 3 && y >= 0 && y < 3) 
            {
                int nmat[3][3];
                for (int i = 0; i < 3; i++) 
                {
                    for (int j = 0; j < 3; j++)
                    {
                        nmat[i][j] = mat[i][j];
                    }
                }
                swap(nmat[x0][y0], nmat[x][y]);
                string p;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++) 
                    {
                        p += to_string(nmat[i][j]);
                    }
                }
                next[c] = "move 0 to " + dir[i];
                flag[c] = p;
                c++;
            }
        }
        cout << c << endl;
        for (int i = 0; i < c; i++)
         {
            cout << next[i] << endl;
            cout << flag[i] << endl;
        }
    }
    return 0;
}