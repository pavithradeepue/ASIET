//Pavithra Deepu E
// S3 CSE AI 47
//Depth First Search

#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
struct Node {
    int dest;
    struct Node* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct Node* head;
};

// Function to create a new adjacency list node
struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the adjacency list
void addEdge(struct AdjList adj[], int s, int t) {
    // Add edge from s to t
    struct Node* newNode = createNode(t);
    newNode->next = adj[s].head;
    adj[s].head = newNode;

    // Add edge from t to s (for undirected graph)
    newNode = createNode(s);
    newNode->next = adj[t].head;
    adj[t].head = newNode;
}

// Recursive function for DFS traversal
void DFSRec(struct AdjList adj[], int visited[], int s) {
    // Mark the current vertex as visited
    visited[s] = 1;

    // Print the current vertex
    printf("%d ", s);

    // Traverse all adjacent vertices that are not visited yet
    struct Node* current = adj[s].head;
    while (current != NULL) {
        int dest = current->dest;
        if (!visited[dest]) {
            DFSRec(adj, visited, dest);
        }
        current = current->next;
    }
}

// Main DFS function to perform DFS for the entire graph
void DFS(struct AdjList adj[], int V) {
    int visited[V]; // Initialize visited array to false

    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    // Loop through all vertices to handle disconnected graph
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            // If vertex i has not been visited, perform DFS from it
            DFSRec(adj, visited, i);
        }
    }
}

int main() {
    int V, E;

    // Input the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Create an array of adjacency lists
    struct AdjList adj[V];

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; i++) {
        adj[i].head = NULL;
    }

    // Input the number of edges
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Input the edges and add them to the graph
    printf("Enter the edges (format: u v where there is an edge between u and v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &u, &v);
        addEdge(adj, u, v);
    }

    // Perform DFS traversal starting from the first vertex
    printf("DFS traversal of the graph:\n");
    DFS(adj, V);

    return 0;
}
