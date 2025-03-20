#include <iostream>
#include <cmath>
using namespace std;
int count(int state[], int size)
{
    int ivr = 0;
    for (int i = 0; i < size; i++) 
    {
        for (int j = i + 1; j < size; j++) 
        {
            if (state[i] > state[j])
            {
                ivr++;
            }
        }
    }
    return ivr;
}
bool move(string in)
{
    int s = in.length();
    int state[s];
    int space = -1;
    for (int i = 0; i < s; i++) 
    {
        char c = in[i];
        if (c >= '0' && c <= '9') 
        {
            state[i] = c - '0';
        } 
        else if (c >= 'A' && c <= 'F') 
        {
            state[i] = 10 + (c - 'A');
        } 
        else if (c >= 'a' && c <= 'f') 
        {
            state[i] = 10 + (c - 'a');
        }
        if (state[i] == 0) 
        {
            space = i; 
        }
    }
    int n = sqrt(s); 
    int empty = space / n; 
    int filter[s - 1];
    int dex = 0;
    for (int i = 0; i < s; i++) 
    {
        if (state[i] != 0) 
        {
            filter[dex] = state[i];
            dex++;
        }
    }
    int ivr = count(filter, s - 1);

    if (n % 2 == 1) 
    {
        return ivr % 2 == 0;
    } 
    else
    {
        return (ivr + empty) % 2 == 0;
    }
}

int main() 
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string in;
        cin >> in;
        if (move(in)) 
        {
            cout << "YES" << endl;
        } 
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}