#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    int V;                         // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix

public:
    // Constructor
    Graph(int V)
    {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0)); // Initialize matrix with 0
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, bool directed = false)
    {
        adjMatrix[u][v] = 1; // Add edge from u to v
        if (!directed)
        {
            adjMatrix[v][u] = 1; // Add edge from v to u for undirected graph
        }
    }

    // Function to display the adjacency matrix
    void display()
    {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                cout << adjMatrix[i][j] << " ";
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

    // Display the adjacency matrix
    g.display();

    return 0;
}