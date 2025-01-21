#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>

using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};

class Graph
{
private:
    int V;                  // Number of vertices
    vector<list<Edge>> adj; // Adjacency list with edges

public:
    // Constructor
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, int weight, bool directed = true)
    {
        Edge edge = {u, v, weight};
        adj[u].push_back(edge);
        if (!directed)
        {
            Edge reverseEdge = {v, u, weight};
            adj[v].push_back(reverseEdge); // Add the edge in the opposite direction for undirected graph
        }
    }

    // Function to display the graph
    void display()
    {
        for (int i = 0; i < V; ++i)
        {
            cout << "Vertex " << i << ":";
            for (const Edge &edge : adj[i])
            {
                cout << " -> " << edge.destination << " (Weight: " << edge.weight << ")";
            }
            cout << endl;
        }
    }

    // A* algorithm
    vector<int> aStar(int start, int goal, const vector<int> &heuristic)
    {
        // Priority queue to store (f(n), vertex)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> openSet;
        openSet.push({0 + heuristic[start], start});

        // Maps to store g(n) and cameFrom
        unordered_map<int, int> gScore;
        unordered_map<int, int> cameFrom;

        // Initialize gScore for all vertices
        for (int i = 0; i < V; ++i)
        {
            gScore[i] = numeric_limits<int>::max();
        }
        gScore[start] = 0;

        while (!openSet.empty())
        {
            int current = openSet.top().second;
            openSet.pop();

            // If we reached the goal, reconstruct the path
            if (current == goal)
            {
                return reconstructPath(cameFrom, current);
            }

            // Explore neighbors
            for (const Edge &edge : adj[current])
            {
                int neighbor = edge.destination;
                int tentative_gScore = gScore[current] + edge.weight;

                if (tentative_gScore < gScore[neighbor])
                {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentative_gScore;
                    int fScore = tentative_gScore + heuristic[neighbor];
                    openSet.push({fScore, neighbor});
                }
            }
        }

        // Return an empty path if there is no path to the goal
        return {};
    }

private:
    // Function to reconstruct the path from start to goal
    vector<int> reconstructPath(unordered_map<int, int> &cameFrom, int current)
    {
        vector<int> totalPath;
        while (cameFrom.find(current) != cameFrom.end())
        {
            totalPath.push_back(current);
            current = cameFrom[current];
        }
        totalPath.push_back(current);                // Add the start node
        reverse(totalPath.begin(), totalPath.end()); // Reverse the path
        return totalPath;
    }
};

// Example heuristic function (for a grid, for instance)
vector<int> exampleHeuristic(int V)
{
    vector<int> heuristic(V);
    for (int i = 0; i < V; ++i)
    {
        heuristic[i] = abs(i - (V - 1)); // Example heuristic: distance to the last vertex
    }
    return heuristic;
}

int main()
{
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 3);

    vector<int> heuristic = exampleHeuristic(5);
    vector<int> path = g.aStar(0, 4, heuristic);

    cout << "Path from 0 to 4: ";
    for (int node : path)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}