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

void Node::merge(map<int, int> cardinality) {
  for (auto it = cardinality.begin(); it != cardinality.end(); ++it) {
    m_colors_cardinality[it->first] += it->second;
  }
}
void Node::visit(vector<Node>& tree) {
  if (m_computed)
    return;
  m_computed = true;
  int& reference = m_colors_cardinality[m_color];
  reference += 1;
  for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) {
    tree[*it].visit(tree);
    this->merge(tree[*it].m_colors_cardinality);
  }
}

bool vertex_increment(const pair<int, int>& one, const pair<int, int>& two) {
  return one.first >= two.first;
}
ostream&  operator<< (ostream& os, const Node& node) {
  os << "Color : " << node.m_color << " Links:";
  for (auto it = node.m_vertices.begin() ; it != node.m_vertices.end(); ++it) {
    os << '\t' << *it;
  }
  os << endl << " Cardinality " << endl;
  for (auto it = node.m_colors_cardinality.begin(); it != node.m_colors_cardinality.end(); ++it) {
    os << it->first << " " << it->second << endl;
  }
  return os;
}

int main() {
  int nodes, queries;
  vector<Node> tree;
  vector<pair<int,int> > queries_array;
  int color;
  
  cin >> nodes >> queries;

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
  // for (auto it = tree.begin(); it != tree.end(); ++it) {
  //   cout << *it << endl;
  // }

  // Gather queries
  for (int i = 0; i < queries; i++) {
    int v, k;
    cin >> v >> k;
    queries_array.push_back(pair<int,int>(v, k));
  }

  // Sort them
  //  sort (queries_array.begin(), queries_array.end(), vertex_increment); // O (logN)
  
  // O(M)
  for (auto it = queries_array.begin(); it != queries_array.end(); it++) {
    Node& target = tree[it->first - 1];
    target.visit(tree);
    
    int result = 0;

    // O(N) Number of color
    for (auto inner_it = target.m_colors_cardinality.begin(); inner_it != target.m_colors_cardinality.end(); ++inner_it) {
      if (inner_it->second >= it->second)
	result++;
    }
    cout << result << endl;
  }

  // for (auto it = tree.begin(); it != tree.end(); ++it) {
  //   cout << *it << endl;
  // }
  
}
