#include <iostream>
#include <vector>
#include <utility>
#include <vector>
/*
 * https://www.spoj.com/problems/PT07X/
 * Complexity O(V + E)
 * TODO: not quite clear why it does not pass last case
 * http://discuss.spoj.com/t/vertex-cover/30039 
 */

using namespace std;
struct node {
  vector<int> children;
};

int solve(vector<node>& graph, bool * V, int node, int parent)
{
  //cout << "solve(" << node << "," << parent << ") " << endl;
  if (graph[node].children.size() == 1 && graph[node].children[0] == parent) {
    //cout << "solve(" << node << ") = " << 0 << endl;
    return 0;
  }

  V[node] = 1;
  // Root case
  int root = 1;
  vector<int>& children = graph[node].children;
  for (auto it = children.begin(); it != children.end(); ++it) {
    if (V[*it])
      continue;
    //cout << "HereI" << endl;
    root += solve(graph, V, *it, node);
  }

  // Non root case
  int non_root = 0;
  vector<int> granchildren;
  for (auto it = children.begin(); it != children.end(); ++it) {
     if (V[*it])
      continue;
    
    non_root += 1;
    struct node child = graph[*it];
    for (auto init = child.children.begin(); init != child.children.end(); ++init) {
      if (V[*init])
	continue;
      // if (*init == node)
      // 	continue;
      //      cout << "HereII" << endl;
      non_root += solve(graph, V, *init, *it);
    }
  }
  
  if (non_root == 0) {
    //cout << "\t solve(" << node << ") = " << root << endl;
    return root;
  }
  int res =  (root > non_root) ? non_root : root;
  //cout << "\t solve(" << node << ") = " << res << "{" << root <<"," << non_root << "}"  << endl;
  return res;
}

int main()
{
  int size;
  bool *V;
  
  cin >> size;

  if (size == 1) {
    cout << 1 << endl;
    return 0;
  }
  
  vector<node> graph(size + 1);
  V = new bool[size + 1]();
  
  for (int i = 0; i < size - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].children.push_back(v);
    graph[v].children.push_back(u);
  }

  cout << solve(graph, V, 1, 0) << endl;
  return 0;
}
