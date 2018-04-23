/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Souce: http://codeforces.com/contest/86/problem/D
 * Complexity: O(MN)
 */
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;


class Node {
public:
  bool                   m_computed;
  int                    m_color;
  int                    m_index;
  vector<int>            m_vertices;
  map<int,int>           m_colors_cardinality;
  
  Node(int color, int idx):m_computed(false), m_color(color), m_index(idx) { };
  void insertEdge(int vertex) { m_vertices.push_back(vertex); }
  void merge(map<int, int> cardinality);
  void visit(vector<Node>& tree);
};

void flatten(Node& root,
	     vector<Node>& tree,
	     vector<int>& flat,
	     vector<int>& E,
	     vector<int>& U,
	     int& time) {
  
  int index = root.m_index;

  flat[time] = index;
  E[index - 1] = time;
  time++;
  for (auto it = root.m_vertices.begin(); it != root.m_vertices.end(); ++it) {
    flatten(tree[*it], tree, flat, E, U, time);
  }
  flat[time] = index;
  U[index - 1] = time;
  time++;
}

void add(vector<int>& colors, Node& node, vector<bool>& found) {
  if (found[node.m_index - 1])
    return;
  colors[node.m_color - 1]++;
  found[node.m_index - 1] = true;
}

void remove(vector<int> colors, Node& node, vector<bool>& found) {
  if (found[node.m_index - 1])
    return;
  colors[node.m_color - 1]--;
  found[node.m_index - 1] = true;
}

int main() {
  int nodes, queries;
  vector<Node> tree;
  vector<pair<int,int> > queries_array;
  int color, time;
  
  cin >> nodes >> queries;
  vector<int> U(nodes), E(nodes), F(nodes * 2);
  time = 0;
  
  // Build the tree
  for (int i = 0; i < nodes; i++) {
    cin >> color;
    tree.push_back(Node(color, i + 1));
  }

  // Insert edges
  for (int i = 0; i < nodes - 1;i++) {
    int a, b;
    cin >> a >> b;

    tree[a - 1].insertEdge(b-1);
    //    tree[b-1].insertEdge(a-1);
  }

  // Create flat array
  flatten(tree[0], tree, F, E, U, time);

  
  for (auto it = F.begin(); it != F.end(); ++it) {
    cout << *it << ",";
  }
  cout << endl;

  for (auto it = E.begin(); it != E.end(); ++it) {
    cout << *it << ",";
  }
  cout << endl;

  for (auto it = U.begin(); it != U.end(); ++it) {
    cout << *it << ",";
  }
  cout << endl;
  
  vector<int> colors(nodes, 0);
  int r, l;
  r = -1;
  l = 0;
  for (int i = 0; i < queries; i++) {
    int v, k;
    int query_l, query_r;
    vector<bool> found(nodes, false);
    
    cin >> v >> k;
    
    // Entrata, Uscita
    query_l = E[v - 1];
    query_r = U[v - 1];
    cout << query_l << "," << query_r << endl;
    while (l < query_l) {
      cout << "l" << l << endl;
      remove(colors, tree[F[l]], found);
      l++;
    }
    while (l > query_l) {
      l--;
      cout << "l" << l << endl;
      add(colors, tree[F[l]], found);
    }
    while(r < query_r) {
      r++;
      cout << "r" << r << endl;
      add(colors, tree[F[r]], found);
    }
    while(r > query_r) {
      cout << "r" << r << endl;
      remove(colors, tree[F[r]], found);
      r--;
    }

    // Print out results
    int result = 0;
    for (auto it = colors.begin(); it != colors.end(); ++it) {
      if (*it > k)
	result++;
    }
    cout << result << endl;
  }
}
