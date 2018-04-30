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
using namespace std;

class query {
public:
  int l, r, pos, count;
  bool operator== (const query& one) {
     return one.l == l && one.r == r;
  }
  friend ostream& operator<<(ostream& os, const query& one);
};

ostream& operator<<(ostream& os, const query& one) {
  os << "{" << one.l << "," << one.r << "}";
  return os;
}

bool right_order(const query& one, const query& two) {
  return one.l < two.l;
}


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

  flat[time] = index - 1; // Normalize ?
  E[index - 1] = time;
  time++;
  for (auto it = root.m_vertices.begin(); it != root.m_vertices.end(); ++it) {
    flatten(tree[*it], tree, flat, E, U, time);
  }
  flat[time] = index - 1;
  U[index - 1] = time;
  time++;
}

void add(vector<int>& colors,
	 Node& node,
	 vector<bool>& found) {
  //  cout << "add()" << node.m_index << endl;
  if (found[node.m_index - 1])
    return;
  //  cout << " incrementing " << node.m_color -1 << endl;
  colors[node.m_color - 1]++;
  //  result = (colors[node.m_color - 1] >= k) ? result + 1 : result;
  found[node.m_index - 1] = true;
}

void remove(vector<int>& colors,
	    Node& node,
	    vector<bool>& found) {
  //cout << "remove()" << node.m_index << endl;

  if (found[node.m_index - 1])
    return;
  //  cout << "decrementing " << node.m_color << endl;
  colors[node.m_color - 1]--;
  //  result = (colors[node.m_color - 1] == k - 1) ? result - 1 : result;
  found[node.m_index - 1] = true;
}

int main() {
  int nodes, queries, color, time;
  vector<Node> tree;
  vector<query>   queries_vector;
  vector<int64_t>        results;
  
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
    //    tree[b-1].insertEdge(a-1); Other direction
  }

  // Create flat array
  flatten(tree[0], tree, F, E, U, time);
  // for (auto it = F.begin(); it != F.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;

  // for (auto it = E.begin(); it != E.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;

  // for (auto it = U.begin(); it != U.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;

  // Store all queries in the buckets
  // int bucket_size = round((float) (nodes * 2 / sqrt(nodes * 2)));
  // int bucket_number = ceil((float) (nodes * 2 / sqrt(nodes * 2)));

  // for (int i = 0; i < bucket_number; i++) {
  //   buckets.push_back(vector<query>());
  // }


  for (int i = 0; i < queries; i++) { // O(Q * lgQ)
    query query;
    int l;

    cin >> l;
    cin >> query.count;
    query.l = E[l - 1];
    query.r = U[l - 1];
    query.pos = i;
    queries_vector.push_back(query);
  }
  sort (queries_vector.begin(), queries_vector.end(), right_order);  // O(SQRT(N)* LG(
  results.reserve(queries);

  // Mo's algorithm
  vector<int> colors(nodes, 0);
  int r, l;
  r = -1;
  l = 0;
  for (auto query_item = queries_vector.begin(); query_item != queries_vector.end(); ++query_item) {

      int query_l, query_r, k;
      vector<bool> found(nodes, false);
    
      // Entrata, Uscita
      query_l = query_item->l;
      query_r = query_item->r;
      k = query_item->count;
      //      cout << query_l << "," << k << endl;
      while (l < query_l) {
	//	cout << "lremove" << l << endl;
	remove(colors, tree[F[l]], found);
	l++;
      }
      while (l > query_l) {
	l--;
	//	cout << "ladd" << l << endl;
	add(colors, tree[F[l]], found);
      }
      while(r < query_r) {
      r++;
      //      cout << "radd" << r << endl; 
      add(colors, tree[F[r]], found);
      }
      while(r > query_r) {
	//	cout << "rremove" << r << endl;
	remove(colors, tree[F[r]], found);
	r--;
      }

      // Print out results
      int result = 0;
      for (auto it = colors.begin(); it != colors.end(); ++it) {
	//	  cout << "Color " << colors.size() - (colors.end() - it) << " count " << *it << endl;
	if (*it >= k)
	  result++;
      }
      results[query_item->pos] = result;
      //      cout << "Writing " << result <<endl;
    }
  for (auto i = 0; i < queries; ++i) { // O(Q) Q = queries
    cout << results[i] << endl;
  }
}
