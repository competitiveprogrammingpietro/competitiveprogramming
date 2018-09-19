#include <iostream>
#include <vector>
#include <utility>
#include <vector>
/*
 * https://www.spoj.com/problems/PT07X/
 * Complexity O(V)
 * TODO: not quite clear why it does not pass last case (11)
 * http://discuss.spoj.com/t/vertex-cover/30039 
 */

using namespace std;
struct node {
  vector<int> children;
};

int V[10001] = { 0 };
int  R[10001] = { 0 };

int solve(vector<node>& graph, int node, int parent)
{
  V[node] = 1;
  int nroot, root;
  //  cout << "Solve(" << node << "," << parent << ")" << endl;
  nroot = root = 0;

  vector<int>& children = graph[node].children;

  // Just a link to the parent
  if (children.size() == 1)
    return 1;
  
  // Non root
  for (auto it = children.begin(); it != children.end(); ++it) {
    if (*it == parent)
      continue;
    R[*it] = solve2(graph, *it, node);
    nroot += R[*it];
  }

  // root
  root = 1;
  for (auto it = children.begin(); it != children.end(); ++it) {
    if (*it == parent)
      continue;
    vector<int>& granchildren = graph[*it].children;
    for (auto init = granchildren.begin(); init != granchildren.end(); ++init) {
      if (*init == node)
	continue;
      if (!V[*init])
	root += solve2(graph, *init, node);
      else
	root += R[*init];
    }
  }

  if (nroot == 0)
    return root;
  else
    return root > nroot ? nroot : root;
}

int main()
{
  int size;
  
  cin >> size;
  V[0] = 1;
  if (size == 1) {
    cout << 0 << endl;
    return 0;
  }
  
  vector<node> graph(size + 1);
  vector<int> res(size + 1);
  
  for (int i = 0; i < size - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].children.push_back(v);
    graph[v].children.push_back(u);
  }
  
  cout << solve(graph,1, 0) << endl;
  return 0;
}
