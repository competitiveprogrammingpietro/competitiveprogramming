#include <iostream>
#include <stack>
#include <list>
#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define MATRIX_SIZE 26

using namespace std;

int G[MATRIX_SIZE][MATRIX_SIZE] = { {0} };

// Topological sort (ish)
void topological_sort(int node, int * VISITED, list<int>& order) {

  if (VISITED[node])
    return;

  VISITED[node] = 1;
  order.push_back(node);
  
  // Add children
  for (int j = 0; j < MATRIX_SIZE; j++) {
    if (G[node][j]) {
      topological_sort(j, VISITED, order);
    }
  }

}


bool cycle = false;


// DFS for cycle detection
int DFS_Cycle(int node, int * VISITED) {
  if (VISITED[node]) {
    cycle = true;
    return 0;
  }
  VISITED[node] = 1;
  
  // Add children
  for (int j = 0; j < MATRIX_SIZE; j++) {
    if (G[node][j]) {
      DFS_Cycle(j, VISITED);
    }
  }
  return 0;
}

int test() {
  int n;
  string a, b;
  
  // Build the graph
  cin >> n;
  cin >> a;
  for (int i = 0; i < n-1; i++) {
    cin >> b;
    
    int min_length = a.length() > b.length() ? a.length() : b.length();
    for (int j = 0; j < min_length; j++) {
      cout << a[j] << "," << b[j] << endl;
      if (a[j] != b[j]) {
	G[a[j] - 'a'][b[j] - 'a'] = 1;
	break;
      }
    }
    a = b;
  }

  char * alphabet = ALPHABET;
  cout << "   ";
  for (int i = 0; i < MATRIX_SIZE; i++) {
    cout << (alphabet[i]);
  }
  cout << endl;
  
  for (int i = 0; i < MATRIX_SIZE; i++) {
    cout << "[" << (char) (i + 'a') << "]";
    for (int j = 0; j < MATRIX_SIZE; j++) {
      cout << G[i][j];
    }
    cout << endl;
  }

  for (int i = 0; i < MATRIX_SIZE; i++) {
    int visited[MATRIX_SIZE] = { 0 };
    DFS_Cycle(i, visited);
  
    if (cycle) {
      cout << "Impossible" << endl;
      return 0;
    }
  }

  list<int> order;
  int visited[MATRIX_SIZE] = { 0 };
  for (int i = 0; i < MATRIX_SIZE; i++) {
    topological_sort(i, visited, order);
  }
    
  for (auto it = order.begin(); it != order.end(); ++it) {
    cout << (char) ('a' + *it) << endl;
  }
  
  return 0;
}

int main() {
  test();
}

