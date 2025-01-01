#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph
{
private:
    int V;                 // Number of vertices
    vector<list<int>> adj; // Adjacency list

public:
    // Constructor
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, bool directed = false)
    {
        adj[u].push_back(v);
        if (!directed)
        {
            adj[v].push_back(u); // Add the edge in the opposite direction for undirected graph
        }
    }

    // Function to display the graph
    void display()
    {
        for (int i = 0; i < V; ++i)
        {
            cout << "Vertex " << i << ":";
            for (int neighbor : adj[i])
            {
                cout << " -> " << neighbor;
            }
            cout << endl;
        }
    }
};

int main()
{
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges (undirected by default)
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Display the graph
    g.display();

    return 0;
}