#include <iostream>
#include <vector>
#include <list>
#include <queue>
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
    void addEdge(int u, int v, int weight, bool directed = false)
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

    // Dijkstra's algorithm to find the shortest path from a source vertex
    void dijkstra(int start)
    {
        vector<int> distance(V, numeric_limits<int>::max());
        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty())
        {
            int current = pq.top().second;
            cout << "current " << current << endl;
            pq.pop();

            if (visited[current])
                continue;
            visited[current] = true;

            cout << "visisted " << current << endl;

            for (const Edge &edge : adj[current])
            {
                int next = edge.destination;
                int weight = edge.weight;

                cout << "Next " << next << ":" << distance[current] << " + " << weight << " < " << distance[next] << endl;

                if (distance[current] + weight < distance[next])
                {
                    distance[next] = distance[current] + weight;
                    pq.push({distance[next], next});
                }
            }
        }

        // Result output
        for (int i = 0; i < V; ++i)
        {
            if (distance[i] == numeric_limits<int>::max())
            {
                cout << "Node " << i << " is unreachable from start node " << start << endl;
            }
            else
            {
                cout << "Distance from start node " << start << " to node " << i << " is " << distance[i] << endl;
            }
        }
    }
};

int main()
{
    Graph g(5); // Create a graph with 5 vertices

    // Add edges with weights
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 2);
    g.addEdge(3, 4, 7);
    g.addEdge(4, 3, 9);

    // Display the graph
    g.display();

    // Run Dijkstra's algorithm from vertex 0
    g.dijkstra(0);

    return 0;
}
