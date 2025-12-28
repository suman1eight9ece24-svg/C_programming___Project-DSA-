#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CITIES 20
#define MAX_NAME_LEN 30

// Queue structure for BFS
typedef struct {
    int items[MAX_CITIES];
    int front, rear;
} Queue;

// Graph structure using adjacency matrix
typedef struct {
    char cityNames[MAX_CITIES][MAX_NAME_LEN];
    int adjMatrix[MAX_CITIES][MAX_CITIES];
    int numCities;
} Graph;

// Queue operations
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// Graph operations
void initGraph(Graph *g) {
    g->numCities = 0;
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

int findCityIndex(Graph *g, const char *cityName) {
    for (int i = 0; i < g->numCities; i++) {
        if (strcmp(g->cityNames[i], cityName) == 0) {
            return i;
        }
    }
    return -1;
}

// ================================= ADD City ================================
void addCity(Graph *g, const char *cityName) {
    if (findCityIndex(g, cityName) == -1 && g->numCities < MAX_CITIES) {
        strcpy(g->cityNames[g->numCities], cityName);
        g->numCities++;
        printf("City '%s' added successfully.\n", cityName);
    } else {
        printf("City '%s' already exists or maximum limit reached.\n", cityName);
    }
}

// ================================= ADD Route ================================
void addRoute(Graph *g, const char *city1, const char *city2) {
    int idx1 = findCityIndex(g, city1);
    int idx2 = findCityIndex(g, city2);
    
    if (idx1 == -1 || idx2 == -1) {
        printf("One or both cities not found!\n");
        return;
    }
    
    g->adjMatrix[idx1][idx2] = 1;
    g->adjMatrix[idx2][idx1] = 1; // Undirected graph
    printf("Route added between '%s' and '%s'.\n", city1, city2);
}

// BFS to find shortest path
bool bfsShortestPath(Graph *g, int start, int end, int *parent) {
    bool visited[MAX_CITIES] = {false};
    Queue q;
    initQueue(&q);
    
    visited[start] = true;
    enqueue(&q, start);
    parent[start] = -1;
    
    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        
        if (current == end) {
            return true;
        }
        
        for (int i = 0; i < g->numCities; i++) {
            if (g->adjMatrix[current][i] && !visited[i]) {
                visited[i] = true;
                parent[i] = current;
                enqueue(&q, i);
            }
        }
    }
    
    return false;
}

void printPath(Graph *g, int *parent, int end) {
    if (parent[end] == -1) {
        printf("%s", g->cityNames[end]);
        return;
    }
    printPath(g, parent, parent[end]);
    printf(" -> %s", g->cityNames[end]);
}

void findShortestPath(Graph *g, const char *city1, const char *city2) {
    int idx1 = findCityIndex(g, city1);
    int idx2 = findCityIndex(g, city2);
    
    if (idx1 == -1 || idx2 == -1) {
        printf("One or both cities not found!\n");
        return;
    }
    
    int parent[MAX_CITIES];
    
    if (bfsShortestPath(g, idx1, idx2, parent)) {
        printf("\nShortest path from '%s' to '%s':\n", city1, city2);
        printPath(g, parent, idx2);
        
        // Count hops
        int hops = 0;
        int curr = idx2;
        while (parent[curr] != -1) {
            hops++;
            curr = parent[curr];
        }
        printf("\nNumber of connections: %d\n", hops);
    } else {
        printf("No route exists between '%s' and '%s'.\n", city1, city2);
    }
}

// DFS to check if route exists
bool dfsHelper(Graph *g, int current, int end, bool *visited) {
    if (current == end) {
        return true;
    }
    
    visited[current] = true;
    
    for (int i = 0; i < g->numCities; i++) {
        if (g->adjMatrix[current][i] && !visited[i]) {
            if (dfsHelper(g, i, end, visited)) {
                return true;
            }
        }
    }
    
    return false;
}

bool checkRouteExists(Graph *g, const char *city1, const char *city2) {
    int idx1 = findCityIndex(g, city1);
    int idx2 = findCityIndex(g, city2);
    
    if (idx1 == -1 || idx2 == -1) {
        printf("One or both cities not found!\n");
        return false;
    }
    
    bool visited[MAX_CITIES] = {false};
    return dfsHelper(g, idx1, idx2, visited);
}

// Find all reachable cities from a given city
void findReachableCities(Graph *g, const char *cityName) {
    int idx = findCityIndex(g, cityName);
    
    if (idx == -1) {
        printf("City not found!\n");
        return;
    }
    
    bool visited[MAX_CITIES] = {false};
    Queue q;
    initQueue(&q);
    
    visited[idx] = true;
    enqueue(&q, idx);
    
    printf("\nCities reachable from '%s':\n", cityName);
    int count = 0;
    
    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        
        if (current != idx) {
            printf("  - %s\n", g->cityNames[current]);
            count++;
        }
        
        for (int i = 0; i < g->numCities; i++) {
            if (g->adjMatrix[current][i] && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
    
    if (count == 0) {
        printf("  No reachable cities found.\n");
    } else {
        printf("Total: %d cities\n", count);
    }
}

void displayGraph(Graph *g) {
    printf("\n=== City Network ===\n");
    printf("Total cities: %d\n\n", g->numCities);
    
    printf("Routes:\n");
    for (int i = 0; i < g->numCities; i++) {
        printf("%s connects to: ", g->cityNames[i]);
        bool hasConnection = false;
        for (int j = 0; j < g->numCities; j++) {
            if (g->adjMatrix[i][j]) {
                printf("%s ", g->cityNames[j]);
                hasConnection = true;
            }
        }
        if (!hasConnection) {
            printf("(no connections)");
        }
        printf("\n");
    }
}

void menu() {
    printf("\n=== City Route Finder ===\n");
    printf("1. Add City\n");
    printf("2. Add Route\n");
    printf("3. Check if Route Exists (DFS)\n");
    printf("4. Find Shortest Path (BFS)\n");
    printf("5. List Reachable Cities\n");
    printf("6. Display Network\n");
    printf("7. Load Sample Data\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

void loadSampleData(Graph *g) {
    addCity(g, "Delhi");
    addCity(g, "Mumbai");
    addCity(g, "Bangalore");
    addCity(g, "Chennai");
    addCity(g, "Kolkata");
    addCity(g, "Hyderabad");
    addCity(g, "Haldia");
    
    addRoute(g, "Delhi", "Mumbai");
    addRoute(g, "Delhi", "Kolkata");
    addRoute(g, "Mumbai", "Haldia");
    addRoute(g, "Mumbai", "Bangalore");
    addRoute(g, "Bangalore", "Chennai");
    addRoute(g, "Bangalore", "Hyderabad");
    addRoute(g, "Chennai", "Hyderabad");
    addRoute(g, "Kolkata", "Chennai");
    
    printf("\nSample city network loaded!\n");
}

int main() {
    Graph g;
    initGraph(&g);
    
    int choice;
    char city1[MAX_NAME_LEN], city2[MAX_NAME_LEN];
    
    while (1) {
        menu();
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch (choice) {
            case 1:
                printf("Enter city name: ");
                fgets(city1, MAX_NAME_LEN, stdin);
                city1[strcspn(city1, "\n")] = 0;
                addCity(&g, city1);
                break;
                
            case 2:
                printf("Enter first city: ");
                fgets(city1, MAX_NAME_LEN, stdin);
                city1[strcspn(city1, "\n")] = 0;
                printf("Enter second city: ");
                fgets(city2, MAX_NAME_LEN, stdin);
                city2[strcspn(city2, "\n")] = 0;
                addRoute(&g, city1, city2);
                break;
                
            case 3:
                printf("Enter source city: ");
                fgets(city1, MAX_NAME_LEN, stdin);
                city1[strcspn(city1, "\n")] = 0;
                printf("Enter destination city: ");
                fgets(city2, MAX_NAME_LEN, stdin);
                city2[strcspn(city2, "\n")] = 0;
                if (checkRouteExists(&g, city1, city2)) {
                    printf("Route EXISTS between '%s' and '%s'.\n", city1, city2);
                } else {
                    printf("No route between '%s' and '%s'.\n", city1, city2);
                }
                break;
                
            case 4:
                printf("Enter source city: ");
                fgets(city1, MAX_NAME_LEN, stdin);
                city1[strcspn(city1, "\n")] = 0;
                printf("Enter destination city: ");
                fgets(city2, MAX_NAME_LEN, stdin);
                city2[strcspn(city2, "\n")] = 0;
                findShortestPath(&g, city1, city2);
                break;
                
            case 5:
                printf("Enter city name: ");
                fgets(city1, MAX_NAME_LEN, stdin);
                city1[strcspn(city1, "\n")] = 0;
                findReachableCities(&g, city1);
                break;
                
            case 6:
                displayGraph(&g);
                break;
                
            case 7:
                loadSampleData(&g);
                break;
                
            case 0:
                printf("Exiting... Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    
    return 0;
}
