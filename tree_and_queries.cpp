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
#include <cmath>
#include <climits>
using namespace std;

class query {
public:
  int l, r, pos, count;
  bool operator== (const query& one) {
     return one.l == l && one.r == r;
  }
  bool operator< (const query& one) const{
    return this->l < one.l;
  }
  friend ostream& operator<<(ostream& os, const query& one);
};

ostream& operator<<(ostream& os, const query& one) {
  os << "{" << one.l << "," << one.r << "}";
  return os;
}

class Node {
public:
  bool                   m_visited;
  int                    m_color;
  int                    m_index;
  vector<int>            m_vertices;
  map<int,int>           m_colors_cardinality;
  
  Node(int color, int idx):m_visited(false), m_color(color), m_index(idx) { };
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
  //  cout << "Flatten() " << index << endl;
     
  
  flat[time] = index - 1;
  E[index - 1] = time;
  time++;
  for (auto it = root.m_vertices.begin(); it != root.m_vertices.end(); ++it) {
    if (E[tree[*it].m_index - 1] == -1)
      flatten(tree[*it], tree, flat, E, U, time);
  }
  flat[time] = index - 1;
  U[index - 1] = time;
  time++;
}

void add(vector<int>& colors,
	 Node& node,
	 vector<bool>& found) {
  //  cout << "Add() " << node.m_color << endl;
  if (found[node.m_index - 1])
    return;
  //  cout << "Add()1 " << node.m_color << endl;
  colors[node.m_color - 1]++;
  found[node.m_index - 1] = true;
}

void remove(vector<int>& colors,
	    Node& node,
	    vector<bool>& found) {
  //  cout << "Remove() " << node.m_color << endl;
  if (found[node.m_index - 1])
    return;
  //  cout << "Remove1() " << node.m_color << endl;
  colors[node.m_color - 1]--;
  found[node.m_index - 1] = true;
}

int main() {
  int nodes, queries, color, time, max;
  vector<Node> tree;

  cin >> nodes >> queries;
  vector<int>     U(nodes, -1), E(nodes, -1), F(nodes * 2, -1);
  vector<query>   queries_vector(queries);
  vector<int64_t> results(queries, 0);
  time = 0;
  max = INT_MIN;
  
  // Build the tree
  for (int i = 0; i < nodes; i++) {
    cin >> color;
    max = (color > max) ? color : max;
    tree.push_back(Node(color, i + 1));
  }

  // Insert edges
  for (int i = 0; i < nodes - 1;i++) {
    int a, b;
    cin >> a >> b;
    tree[a - 1].insertEdge(b - 1);
    tree[b - 1].insertEdge(a - 1);
  }

  // Create flat array
  flatten(tree[0], tree, F, E, U, time);
#ifdef DEBUG  
  for (auto it = F.begin(); it != F.end(); ++it) {
    cout << *it + 1 << ",";
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
#endif
  for (int i = 0; i < queries; i++) { // O(Q * lgQ)
    query query;
    int l;

    cin >> l;
    cin >> query.count;
    query.l = E[l - 1];
    query.r = U[l - 1];
    query.pos = i;
    queries_vector[i] = query;
  }
  sort (queries_vector.begin(), queries_vector.begin() + queries);
  results.reserve(queries);

  // Mo's algorithm
  vector<int> colors(max, 0);
  int r, l;
  r = -1;
  l = 0;
  for (auto query_item = queries_vector.begin();
       query_item != queries_vector.end();
       ++query_item) {

      int query_l, query_r, k;
      vector<bool> foundl(nodes, false);
      vector<bool> foundr(nodes, false);
    
      // Entrata, Uscita
      query_l = query_item->l;
      query_r = query_item->r;
      k = query_item->count;
      while (l < query_l) {
	remove(colors, tree[F[l]], foundl);
	l++;
      }
      while (l > query_l) {
	l--;
	add(colors, tree[F[l]], foundl);
      }
      while(r < query_r) {
      r++;
      add(colors, tree[F[r]], foundr);
      }
      while(r > query_r) {
	remove(colors, tree[F[r]], foundr);
	r--;
      }

      // Print out results
      int result = 0;
      for (auto it = colors.begin(); it != colors.end(); ++it) {
	if (*it >= k)
	  result++;
      }
      results[query_item->pos] = result;
    }
  for (auto i = 0; i < queries; ++i) { // O(Q) Q = queries
    cout << results[i] << endl;
  }
  return 0;
}
