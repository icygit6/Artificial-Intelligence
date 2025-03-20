#include <iostream>
#include <cmath>
using namespace std;

int main()
 {
    int n;
    cin >> n;
    int mat[3][3] = 
    {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };
    for (int i = 0; i < n; i++) 
    {
        string state;
        cin >> state; 
        int current[3][3];
        int index = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++) 
            {
                current[i][j] = state[index++] - '0';
            }
        }

        int dist = 0;
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                int value = current[i][j];
                if (value != 0) 
                { 
                    for (int k = 0; k < 3; k++) 
                    {
                        for (int l = 0; l < 3; l++) 
                        {
                            if (mat[k][l] == value) 
                            {
                                dist += abs(i - k) + abs(j - l);
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout << dist << endl;
    }

    return 0;
}