#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Goal state
const string GOAL = "012345678";

// Structure to represent each state in the puzzle
struct Node
 {
    string state;    // Current board configuration (e.g., "123456780")
    string path;     // Sequence of moves to reach this state
    int g;           // Cost from start to current state (number of moves)
    int h;           // Heuristic estimate to goal (Manhattan distance)
    int f;           // Total cost (g + h)
    int order;       // For tie-breaking (FIFO when f values are equal)
    
    Node(string s, string p, int gval, int hval, int o) : 
        state(s), path(p), g(gval), h(hval), f(gval + hval), order(o) {}
};

// Custom comparator for priority queue
struct comp 
{
    // Defines how nodes are ordered in the priority queue
    bool operator()(const Node& a, const Node& b) 
    {
        if (a.f != b.f) 
        {
            return a.f > b.f;  // Lower f has higher priority
        } 
        else 
        {
            return a.order > b.order;  // Earlier insertion has priority when f is equal
        }
    }
};

// Calculates Manhattan distance heuristic
int mandist(const string& state) 
{
    int distance = 0;
    for (int i = 0; i < 9; i++) 
    {
        if (state[i] == '0') continue;  // Skip empty tile
        
        int val = state[i] - '0';      // Convert char to number (1-8)
        int goal_row = val / 3;        // Goal row position
        int goal_col = val % 3;        // Goal column position
        int curr_row = i / 3;          // Current row position
        int curr_col = i % 3;          // Current column position
        
        distance += abs(goal_row - curr_row) + abs(goal_col - curr_col);  // Add tile's distance
    }
    return distance;
}

// Checks if puzzle is solvable by counting inversions
bool solving(const string& state) 
{
    int inversions = 0;
    for (int i = 0; i < 9; i++) 
    {
        if (state[i] == '0') continue;  // Skip empty tile
        for (int j = i + 1; j < 9; j++)
        {
            if (state[j] != '0' && state[i] > state[j]) 
            {
                inversions++;  // Count out-of-order pairs
            }
        }
    }
    return (inversions % 2) == 0;  // Solvable if even number of inversions
}

// Generates all possible next moves from current state
vector<pair<string, string>> getMoves(const string& state) 
{
    vector<pair<string, string>> moves;
    int pos = state.find('0');  // Find empty tile position
    int row = pos / 3;          // Current row of empty tile
    int col = pos % 3;          // Current column of empty tile

    // Possible movement directions (up, down, left, right)
    int dr[] = {-1, 1, 0, 0};  // Row changes
    int dc[] = {0, 0, -1, 1};  // Column changes
    string dir[] = {"up", "down", "left", "right"};  // Direction names

    for (int i = 0; i < 4; i++) 
    {
        int nrow = row + dr[i];  // New row after move
        int ncol = col + dc[i];  // New column after move
        
        // Check if move is within board boundaries
        if (nrow >= 0 && nrow < 3 && ncol >= 0 && ncol < 3) 
        {
            int npos = nrow * 3 + ncol;  // Convert to linear position
            string nstate = state;        // Create copy of current state
            swap(nstate[pos], nstate[npos]);  // Swap empty tile with neighbor
            
            moves.push_back({nstate, dir[i]});  // Add new state and move direction
        }
    }
    return moves;
}

// A* search algorithm to solve the puzzle
string solve(const string& intl) 
{
    if (intl == GOAL) return "It is the goal state.";  // Already solved
    if (!solving(intl)) return "No solution!!";     // Unsolvable puzzle

    priority_queue<Node, vector<Node>, comp> open;     // Priority queue for open nodes
    unordered_map<string, bool> closed;                // Track visited states
    int order_counter = 0;                             // For tie-breaking

    open.push(Node(intl, "", 0, mandist(intl), order_counter++));  // Add initial state

    while (!open.empty()) 
    {
        Node current = open.top();  // Get most promising state
        open.pop();

        if (current.state == GOAL)  // Check if goal reached
        {
            return current.path;    // Return solution path
        }

        if (closed[current.state]) continue;  // Skip already visited states
        closed[current.state] = true;         // Mark as visited

        vector<pair<string, string>> moves = getMoves(current.state);  // Generate next moves
        for (auto& move : moves) 
        {
            if (!closed[move.first])  // If state not visited
            {
                int h = mandist(move.first);  // Calculate heuristic
                string new_path = current.path;         // Build path string
                if (!new_path.empty()) new_path += "\n";
                new_path += "move 0 to " + move.second;
                
                open.push(Node(move.first, new_path, current.g + 1, h, order_counter++));  // Add to queue
            }
        }
    }
    return "No solution!!";  // If no solution found
}

int main()
 {
    string initial;
    cin >> initial;  // Read initial state
    string solution = solve(initial);  // Solve puzzle
    cout << solution << endl;          // Output solution
    return 0;
}