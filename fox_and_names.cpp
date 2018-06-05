#include <iostream>
#include <stack>
#include <list>
#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define MATRIX_SIZE 26

using namespace std;

int G[MATRIX_SIZE][MATRIX_SIZE] = { {0} };
int PRESENT[MATRIX_SIZE] = { 0 };

// Topological sort (ish)
void topological_sort(int node, int * VISITED, list<int>& order) {
  //cout << "Topological " << (char) ('a' + node) << endl;
  if (!PRESENT[node])
    return;
  
  if (VISITED[node])
    return;

  VISITED[node] = 1;
  
  // Add children
  for (int j = 0; j < MATRIX_SIZE; j++) {
    if (G[node][j]) {
      topological_sort(j, VISITED, order);
    }
  }
  order.push_front(node);
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

int __attribute__((optimize("O0"))) test() {
  int n;
  string a, b;
  
  // Build the graph
  cin >> n;
  cin >> a;
  for (int i = 0; i < n-1; i++) {
    cin >> b;

    bool found = false;
    int min_length = a.length() < b.length() ? a.length() : b.length();
    for (int j = 0; j < min_length; j++) {
      if (a[j] != b[j]) {
	G[a[j] - 'a'][b[j] - 'a'] = 1;
	PRESENT[a[j] - 'a'] = PRESENT[b[j] - 'a'] = 1;
	break;
      }

      if (!found && b.length() < a.length()) {
	printf("Impossible\n");
	return 0;
      }
	
    }
    a = b;
    
  }

  // char * alphabet = ALPHABET;
  // cout << "   ";
  // for (int i = 0; i < MATRIX_SIZE; i++) {
  //   cout << (alphabet[i]);
  // }
  // cout << endl;
  
  // for (int i = 0; i < MATRIX_SIZE; i++) {
  //   cout << "[" << (char) (i + 'a') << "]";
  //   for (int j = 0; j < MATRIX_SIZE; j++) {
  //     cout << G[i][j];
  //   }
  //   cout << endl;
  // }

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
    if (PRESENT[i])
      topological_sort(i, visited, order);
  }

  for (int i = 0; i < MATRIX_SIZE; i++) {
    if (order.front() == i) {
      for (auto it = order.begin(); it != order.end(); ++it)
	cout << (char) (*it + 'a');
    } else {
      if (!PRESENT[i]) {
	printf("%c", (char) (i + 'a'));
      }
      //	cout << (char) (i + 'a');
    }
      
  }
    
  // for (auto it = order.begin(); it != order.end(); ++it) {
  //   cout << (char) ('a' + *it) << endl;
  // }
  printf("\n");
  //  cout << endl;
  
  return 0;
}

int main() {
  test();
  return 0;
}

