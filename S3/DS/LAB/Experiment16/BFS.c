//Pavithra Deepu E
// S3 CSE AI 47
//Breadth First Search

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// BFS from the given source s
void bfs(int adj[MAX][MAX], int V, int s) {
    // Create a queue for BFS
    int q[MAX], front = 0, rear = 0;
    
    // Initially mark all the vertices as not visited
    bool visited[MAX] = { false };
    
    // Mark the source node as visited and enqueue it
    visited[s] = true;
    q[rear++] = s;
    
    // Iterate over the queue
    while (front < rear) {
        // Dequeue a vertex and print it
        int curr = q[front++];
        printf("%d ", curr);
        
        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent has not been visited, mark it visited and enqueue it
        for (int i = 0; i < V; i++) {
            if (adj[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                q[rear++] = i;
            }
        }
    }
}

// Function to add an edge to the graph
void addEdge(int adj[MAX][MAX], int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;  // Undirected graph
}

int main() {
    int V, E, u, v;

    // Input the number of vertices in the graph
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Initialize the adjacency matrix to 0 (no edges)
    int adj[MAX][MAX] = {0};

    // Input the number of edges
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Add edges to the graph
    for (int i = 0; i < E; i++) {
        printf("Enter edge %d (u v): ", i + 1);
        scanf("%d %d", &u, &v);
        // Add the edge to the graph
        addEdge(adj, u, v);
    }

    // Input the starting vertex for BFS
    int start;
    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &start);

    // Perform BFS traversal starting from the user-provided vertex
    printf("BFS starting from vertex %d:\n", start);
    bfs(adj, V, start);

    return 0;
}
