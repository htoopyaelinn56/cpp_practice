#include <iostream>
#include <vector>
#include <limits>

// Structure to represent an edge
struct Edge {
    int source;
    int destination;
    int weight;
};

class BellmanFord {
private:
    int V;  // Number of vertices
    int E;  // Number of edges
    std::vector<Edge> edges;
    std::vector<int> distances;

public:
    // Constructor
    BellmanFord(int vertices) {
        V = vertices;
        E = 0;
    }

    // Add an edge to the graph
    void addEdge(int source, int destination, int weight) {
        Edge edge;
        edge.source = source;
        edge.destination = destination;
        edge.weight = weight;
        edges.push_back(edge);
        E++;
    }

    // Main Bellman-Ford algorithm implementation
    bool findShortestPaths(int sourceVertex) {
        // Step 1: Initialize distances
        distances.resize(V, std::numeric_limits<int>::max());
        distances[sourceVertex] = 0;

        // Step 2: Relax all edges V-1 times
        for (int i = 1; i <= V - 1; i++) {
            for (const Edge& edge : edges) {
                int u = edge.source;
                int v = edge.destination;
                int weight = edge.weight;

                // Relaxation step
                if (distances[u] != std::numeric_limits<int>::max() &&
                    distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                }
            }
        }

        // Step 3: Check for negative weight cycles
        for (const Edge& edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;

            // If we can still relax an edge, a negative cycle exists
            if (distances[u] != std::numeric_limits<int>::max() &&
                distances[u] + weight < distances[v]) {
                return false;  // Negative weight cycle detected
            }
        }

        return true;  // No negative weight cycle
    }

    // Print shortest distances
    void printDistances() {
        std::cout << "Vertex\tDistance from Source\n";
        for (int i = 0; i < V; i++) {
            if (distances[i] == std::numeric_limits<int>::max()) {
                std::cout << i << "\t\tINFINITY\n";
            } else {
                std::cout << i << "\t\t" << distances[i] << "\n";
            }
        }
    }
};

int main() {
    // Example usage
    BellmanFord graph(5);

    // Adding edges
    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    // Find shortest paths from vertex 0
    if (graph.findShortestPaths(0)) {
        std::cout << "Shortest paths found successfully:\n";
        graph.printDistances();
    } else {
        std::cout << "Negative weight cycle detected!\n";
    }

    return 0;
}