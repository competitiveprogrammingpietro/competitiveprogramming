#include <iostream>
#include <utility>
#include <list>
#include <vector>

using namespace std;

#define MAX 50

/*
 * Source : https://practice.geeksforgeeks.org/problems/x-total-shapes/0
 * O(MN)
 */
struct graph {
  int matrix[MAX + 1][MAX + 1] = { {0} };
  int color[MAX + 1][MAX + 1] = { {0} };
  pair<int, int> size; // Row, Column
  int root_i, root_j;
  int next_colors = 1;
  
  pair<int, int> BFS(int sc, int sr);
  vector<pair<int, int>> adjacent(int r, int c);
  pair<int, int> next(int r, int c);
  void print_color();
  void print_graph();
};

void graph::print_color() {
  cout << endl;
  cout << "[";
   for (int i = 0; i < size.first; i++) {
    for (int j = 0; j < size.second; j++) {
      cout << color[i][j] << " ";
    }
    cout << endl;
   }
   cout << "]" << endl;
}


void graph::print_graph() {
  cout << endl;
  cout << "[";
   for (int i = 0; i < size.first; i++) {
    for (int j = 0; j < size.second; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
   }
   cout << "]" << endl;
}

pair<int, int> graph::next(int r, int c) {
  if (r == size.first - 1 && c == size.second -1)
    return pair<int, int>(0, 0);
  
  for (int i = r; i < size.first; i++) {
    int j = (i == r) ? c : 0;
    for (; j < size.second; j++) {
      if (matrix[i][j] && color[i][j] == 0)
	return pair<int, int>(i, j);
    }
  }
  return pair<int, int>(0, 0);
}

pair<int, int> graph::BFS(int sc, int sr) {
  list<pair<int, int>> Q; // Row, Column
  int set_color = this->next_colors++;
  
  Q.push_back(pair<int, int>(sc, sr));

  pair<int, int> node;
  while (!Q.empty()) {
    //    cout << Q.size() << endl;
    node = Q.front();
    Q.pop_front();

    // Already visited
    if (color[node.first][node.second] != 0)
      continue;

    // Not a node
    if (matrix[node.first][node.second] == 0)
      continue;
    
    // Assign color
    color[node.first][node.second] = set_color;
    
    // Adjacent
    if (node.first - 1 >= 0)
      Q.push_back(pair<int, int>(node.first - 1, node.second));
    if (node.first + 1 < size.first)
      Q.push_back(pair<int, int>(node.first + 1, node.second));
    if (node.second - 1 >= 0)
      Q.push_back(pair<int, int>(node.first, node.second - 1));
    if (node.second + 1 < size.second)
      Q.push_back(pair<int, int>(node.first, node.second + 1));
  }
  return node;
}


int test() {
  int m, n, si, sj;
  struct graph tree;

  // Build the graph
  cin >> n >> m;
  tree.size.first = n;
  tree.size.second = m;
  
  //  cout << endl;
  si = sj = -1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char X;

      cin >> X;
      //cout << X;
      if (X != 'X')
	continue;
      if (si == -1) {
	si = i;
	sj = j;
      }
      //cout << "Tree" << i << j << " 1" << endl;
      tree.matrix[i][j] = 1;
    }
    //cout << endl;
  }
  //cout << endl;

  pair<int, int> source = tree.next(0, 0);
  //cout << "Source " << source.first << "," << source.second << endl;
  while (true) {
    tree.BFS(source.first, source.second);
     // tree.print_color();
     // tree.print_graph();
    //cout << "Source " << source.first << "," << source.second << endl;
    source = tree.next(source.first, source.second);
    //cout << "Source " << source.first << "," << source.second << endl;
    if (source.first == 0 && source.second == 0)
      return tree.next_colors - 1;
  }
}


int main() {
  int tests;

  cin >> tests;
  for (int i = 0; i < tests; i++) {
    int result = test();
    cout << result << endl;
  }
  return 0;
}
