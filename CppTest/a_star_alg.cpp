#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <set>
#include <algorithm> // For std::reverse

using namespace std;

// Define a class to represent a point in the grid
class Node
{
public:
    int x, y; // Coordinates
    float g;  // Cost from start to this node
    float h;  // Heuristic cost to goal
    float f;  // Total cost (g + h)

    // Default constructor
    Node() : x(0), y(0), g(0), h(0), f(0) {}

    // Constructor to initialize x, y, g, h, and f
    Node(int x, int y, float g = 0, float h = 0) : x(x), y(y), g(g), h(h)
    {
        f = g + h; // Calculate f based on g and h
    }

    // Overload the > operator for priority queue
    bool operator>(const Node &other) const
    {
        return f > other.f;
    }

    // Overload the == operator for easy comparison
    bool operator==(const Node &other) const
    {
        return x == other.x && y == other.y;
    }
};

// Function to calculate the Euclidean distance heuristic
float euclideanDistance(const Node &a, const Node &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// A* algorithm implementation
vector<Node> aStar(Node start, Node goal, const vector<vector<int>> &grid)
{
    cout << "start (" << start.x << "," << start.y << ")" << endl;
    cout << "goal (" << goal.x << "," << goal.y << ")" << endl;
    cout << "---" << endl;

    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    set<pair<int, int>> closedSet;
    unordered_map<int, Node> allNodes;
    unordered_map<int, Node> cameFrom; // To store the path

    start.h = euclideanDistance(start, goal);
    start.f = start.g + start.h;
    openSet.push(start);

    while (!openSet.empty())
    {
        Node current = openSet.top();
        cout << "current node: (" << current.x << "," << current.y << ")" << endl;
        openSet.pop();

        // If we reached the goal, reconstruct the path
        if (current == goal)
        {
            cout << "found goal" << endl;
            vector<Node> path;
            Node temp = current;
            while (cameFrom.find(temp.x * grid[0].size() + temp.y) != cameFrom.end())
            {
                path.push_back(temp);
                temp = cameFrom[temp.x * grid[0].size() + temp.y];
            }
            path.push_back(start);             // Add the start node
            reverse(path.begin(), path.end()); // Reverse the path to get it from start to goal
            return path;
        }

        closedSet.insert({current.x, current.y});

        // Explore neighbors (4 possible directions)
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto &dir : directions)
        {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            cout << "exploring (" << newX << "," << newY << ")" << endl;

            // Check if the new position is within bounds and not blocked
            if (newX >= 0 && newY >= 0 && newX < grid.size() && newY < grid[0].size() && grid[newX][newY] == 0)
            {
                Node neighbor(newX, newY);
                if (closedSet.count({newX, newY}))
                    continue; // Already evaluated

                neighbor.g = current.g + 1; // Assuming cost to move to neighbor is 1
                neighbor.h = euclideanDistance(neighbor, goal);
                neighbor.f = neighbor.g + neighbor.h;

                // Check if this path to neighbor is better
                if (allNodes.find(newX * grid[0].size() + newY) == allNodes.end() || neighbor.g < allNodes[newX * grid[0].size() + newY].g)
                {
                    allNodes[newX * grid[0].size() + newY] = neighbor;
                    cameFrom[newX * grid[0].size() + newY] = current; // Store the current node as the parent
                    openSet.push(neighbor);
                    cout << "pushed to cameFrom (" << current.x << "," << current.y << ") to index " << newX * grid[0].size() + newY << endl;
                    cout << "pushed to allNodes (" << neighbor.x << "," << neighbor.y << ")" << endl;
                }
            }
        }
    }

    return {}; // Return an empty path if no path is found
}

int main()
{
    // Example grid (0 = free, 1 = blocked)
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    Node start(0, 0); // Starting point
    Node goal(4, 4);  // Goal point

    vector<Node> path = aStar(start, goal, grid);

    // Output the path
    if (!path.empty())
    {
        cout << "Path found:\n";
        for (const Node &node : path)
        {
            cout << "(" << node.x << ", " << node.y << ") ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found." << endl;
    }

    return 0;
}