/*
 * Competive Programming - UniPi.
 * Souce: http://codeforces.com/contest/86/problem/D
 * Complexity: O(N*SQRT(N))
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX_NODES (100000 + 10)
using namespace std;

int bucket_size;
class query {
public:
  int l, r, pos, count;
  bool operator== (const query& one) {
     return one.l == l && one.r == r;
  }
  bool operator< (const query& one) const {
    if (this->l/bucket_size < one.l/bucket_size)
      return true;
    else if (this->l/bucket_size == one.l/bucket_size)
      return this->r < one.r;
    else
      return false;
  }
  friend ostream& operator<<(ostream& os, const query& one);
};

ostream& operator<<(ostream& os, const query& one) {
  os << "{" << one.l << "," << one.r << "}";
  return os;
}

class Node {
public:
  int                    m_color;
  vector<int>            m_vertices;
  void insertEdge(int vertex) { m_vertices.push_back(vertex); }
};


int color_counter[MAX_NODES] = { 0 };
int k_counters[MAX_NODES] = { 0 };
int F[MAX_NODES] = { 0 };
int U[MAX_NODES] = { 0 };
int E[MAX_NODES] = { 0 };
bool visited[MAX_NODES] = { false };
query Q[MAX_NODES];
int results[MAX_NODES] = { 0 };  
Node tree[MAX_NODES];



void flatten(int node_index,
	     int& time) {
  visited[node_index] = true;
  Node* node = &tree[node_index];
  F[time] = node->m_color;
  E[node_index] = time;
  for (auto it = node->m_vertices.begin(); it != node->m_vertices.end(); ++it) {
    if (!visited[*it])
      flatten(*it, ++time);
  }
  U[node_index] = time;
}

void add(int index) {
#ifdef DEBUG
  cout << "add("
       << index
       << "):"
       << F[index]
       << endl;
#endif  
  int color = F[index];
  color_counter[color]++;
  k_counters[color_counter[color]]++;
}

void remove(int index) {
#ifdef DEBUG
    cout << "remove("
       << index
       << "):"
       << F[index]
       << endl;
#endif  
  int color = F[index];
  k_counters[color_counter[color]]--;
  color_counter[color]--;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); // Fast read
  int nodes, queries, time;

  cin >> nodes >> queries;
  time = 0;
  bucket_size = sqrt(queries);
  
  // Create tree
  int color;
  for (int i = 0; i < nodes; i++) {
    cin >> color;
    tree[i].m_color = color;
    tree[i].m_vertices.clear();
  }

  // Insert edges
  for (int i = 0; i < nodes - 1;i++) {
    int a, b;
    cin >> a >> b;
    tree[a - 1].insertEdge(b - 1);
    tree[b - 1].insertEdge(a - 1);
  }

  // Create flat array
  flatten(0, time);
#ifdef DEBUG  
  for (int i = 0; i < nodes; i++) {
    cout << F[i] << ",";
  }
  cout << endl;
  for (int i = 0; i < nodes; i++) {
    cout << E[i] << ",";
  }
  cout << endl;
  for (int i = 0; i < nodes; i++) {
    cout << U[i] << ",";
  }
  cout << endl;
#endif
  for (int i = 0; i < queries; i++) { 
    int l;

    cin >> l;
    cin >> Q[i].count;
    Q[i].l = E[l - 1];
    Q[i].r = U[l - 1];
    Q[i].pos = i;
  }
  sort (Q, Q + queries); // O(Q * lgQ)
  
  // Mo's algorithm
  int r, l;
  //  r = -1;
  l = Q[0].l;
  r = l - 1;
  for (int q = 0; q < queries; q++) {
    query * query = &Q[q];
    int query_l, query_r, k;
      
      // Entrata, Uscita
      query_l = query->l;
      query_r = query->r;
      k = query->count;
#ifdef DEBUG      
      cout << Q[q] << endl;
#endif      
      while (l < query_l) {
	remove(l++);
      }
      while (l > query_l) {
	add(--l);
      }
      while(r < query_r) {
	add(++r);
      }
      while(r > query_r) {
	remove(r--);
      }
      results[query->pos] = k_counters[k];
  }
  for (int i = 0; i < queries; ++i) {
    cout << results[i] << endl;
  }
  return 0;
}
