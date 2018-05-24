#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include <stack>

using namespace std;

#define MAX 50

enum Partition { NONE, FIRST, SECOND };
Partition partitions[MAX];
bool error = false;

void DFS(int G[][MAX], int V, int node) {

  Partition children_color = (partitions[node] == FIRST) ? SECOND : FIRST;
  
  for (int i = 0; i < V; i++) {

    // No edge
    if (!G[node][i])
      continue;

    
    // Already visited and correct
    if (partitions[i] == children_color)
      continue;
    
    // Visited but incorrect
    if (partitions[i] != NONE && partitions[i] != children_color) {
      //cout << node << " Failed to give color to " << i << " whose is already " << partition[i] << " instead of " << children_color << endl;
      error = true;
      return;
    }
    // Continue visiting
    partitions[i] = children_color;
    DFS(G, V, i);
  }
}

bool isBipartite(int G[][MAX], int V) {
  for (int i = 0; i < V; i++) {
    partitions[i] = NONE;
  }
  
  for (int i = 0; i < V; i++) {
    if (partitions[i] != NONE)
      continue;
    if (partitions[i] == NONE)
      partitions[i] = FIRST;
    DFS(G, V, i);
  }
  return !error;
}



int G[MAX][MAX];
int test() {
  int n;

  
  // Build the graph
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x;

      cin >> x;
      //cout << "Tree" << i << j << " " << x << endl;
      G[i][j] = x;
    }
    //cout << endl;
  }
  //cout << endl;
  //tree.print_graph();
  cout << isBipartite(G, n) << endl;
  return 0;
}


int main() {
  int tests;

  cin >> tests;
  for (int i = 0; i < tests; i++) {
    int result = test();
    //    cout << result << endl;
  }
  return 0;
}

