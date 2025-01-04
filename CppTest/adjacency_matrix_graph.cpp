#include <iostream>
#include <vector>
#include <set>

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

    void displayConnections()
    {
        cout << "Adjacency Matrix Connections:" << endl;
        for (int i = 0; i < V; ++i)
        {
            cout << i << " = ";
            for (int j = 0; j < V; ++j)
            {
                if (adjMatrix[i][j])
                {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }

    // DFS utility function
    void dfsUtil(int vertex, set<int> &visited)
    {
        visited.insert(vertex); // Mark the current vertex as visited
        cout << vertex << " ";  // Print the current vertex

        // Recur for all the vertices adjacent to this vertex
        for (int i = 0; i < V; ++i)
        {
            if (adjMatrix[vertex][i] && visited.count(i) == 0)
            {
                dfsUtil(i, visited);
            }
        }
    }

    // Function to perform DFS
    void dfs(int start)
    {
        set<int> visited; // Set to keep track of visited vertices
        cout << "DFS (Adjacency Matrix): ";
        dfsUtil(start, visited); // Start DFS from the given vertex
        cout << endl;
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
    g.displayConnections();

    g.dfs(1);

    return 0;
}