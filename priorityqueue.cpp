#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct node 
{
    string state;  // Stores the puzzle state (e.g., "724560831")
    int g;         // Cost from start to current state
    int h;         // Heuristic estimate to goal
    int f;         // Total cost (f = g + h)
    int order;     // Tracks insertion order for tie-breaking
    
    // Constructor to initialize node values
    node(string s, int gval, int hval, int o) : 
        state(s), g(gval), h(hval), f(gval + hval), order(o) {}
};
struct comp 
{
    // Overloads the () operator to compare two nodes
    bool operator()(const node& a, const node& b) 
    {
        if (a.f != b.f) 
        {
            // Lower 'f' has higher priority
            return a.f > b.f;  
        } 
        else 
        {
            // If 'f' is equal, earlier insertion (lower 'order') has priority
            return a.order > b.order;
        }
    }
};

int main() 
{
    // Declare a priority queue using the custom comparator
    priority_queue<node, vector<node>, comp> pq;
    
    int n;          // Number of test cases
    cin >> n;       // Read number of test cases
    
    int inor = 0;   // Tracks insertion order (for tie-breaking)
    
    // Process each test case
    for (int i = 0; i < n; i++) 
    {
        string action;
        cin >> action;  // Read "enqueue" or "dequeue"
        
        if (action == "enqueue") 
        {
            string state;
            int g, h;
            cin >> state >> g >> h;  // Read state, g, h
            
            // Create node and push to priority queue
            pq.push(node(state, g, h, inor++));
            cout << "Insert OK!" << endl;
        } 
        else if (action == "dequeue")
        {
            if (pq.empty()) 
            {
                cout << "Queue is empty!!" << endl;
            } 
            else 
            {
                // Get and remove the top node (lowest f, earliest if tied)
                node top = pq.top();
                pq.pop();
                cout << "Got " << top.state << endl;
            }
        }
    }
    return 0;
}