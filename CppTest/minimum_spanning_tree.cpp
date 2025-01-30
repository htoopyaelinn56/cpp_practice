#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge
{
    int src, dest, weight;
};

// Graph class definition
class Graph
{
public:
    int V;                              // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list with weights

    // Constructor
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, int weight, bool directed = false)
    {
        adj[u].push_back({v, weight});
        if (!directed)
        {
            adj[v].push_back({u, weight}); // Add the edge in the opposite direction for undirected graph
        }
    }

    // Function to display the graph
    void display()
    {
        for (int i = 0; i < V; ++i)
        {
            cout << "Vertex " << i << ":";
            for (auto &neighbor : adj[i])
            {
                cout << " -> " << neighbor.first << " (weight: " << neighbor.second << ")";
            }
            cout << endl;
        }
    }

    // Function to extract all edges from the adjacency list
    vector<Edge> getAllEdges()
    {
        vector<Edge> edges;
        for (int u = 0; u < V; ++u)
        {
            for (auto &neighbor : adj[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;
                // Avoid adding duplicate edges for undirected graphs
                if (u < v)
                {
                    edges.push_back(Edge{u, v, weight});
                }
            }
        }
        return edges;
    }
};

// Disjoint Set (Union-Find) implementation
class DisjointSet
{
public:
    vector<int> parent, rank;

    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Comparator to sort edges by weight
bool compareEdges(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

// Kruskal's algorithm to find MST
void kruskalMST(Graph &graph)
{
    int V = graph.V;
    vector<Edge> edges = graph.getAllEdges();

    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Initialize disjoint set
    DisjointSet ds(V);

    vector<Edge> mst; // To store MST edges
    int totalWeight = 0;

    // Process each edge
    for (const Edge &edge : edges)
    {
        int rootSrc = ds.find(edge.src);
        int rootDest = ds.find(edge.dest);

        // If including this edge doesn't form a cycle
        if (rootSrc != rootDest)
        {
            mst.push_back(edge);
            totalWeight += edge.weight;
            ds.unionSets(rootSrc, rootDest);
        }
    }

    // Print the MST
    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (const Edge &edge : mst)
    {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
    cout << "Total Weight of MST: " << totalWeight << endl;
}

int main()
{
    // Create a graph with 5 vertices
    Graph g(5);

    // Add weighted edges to the graph
    g.addEdge(0, 1, 2); // Edge between vertex 0 and 1 with weight 2
    g.addEdge(0, 3, 6); // Edge between vertex 0 and 3 with weight 6
    g.addEdge(1, 2, 3); // Edge between vertex 1 and 2 with weight 3
    g.addEdge(1, 3, 8); // Edge between vertex 1 and 3 with weight 8
    g.addEdge(1, 4, 5); // Edge between vertex 1 and 4 with weight 5
    g.addEdge(2, 4, 7); // Edge between vertex 2 and 4 with weight 7
    g.addEdge(3, 4, 9); // Edge between vertex 3 and 4 with weight 9

    // Display the graph
    cout << "Graph Representation:\n";
    g.display();

    // Find and print the MST using Kruskal's algorithm
    kruskalMST(g);

    return 0;
}