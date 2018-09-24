#include <iostream>
#include <vector>
#include <utility>
#include <vector>
#include <algorithm>

/*
 * https://www.spoj.com/problems/PT07X/
 * Complexity O(V)
 */

using namespace std;
struct node {
  vector<int> children;
};

int V[100001][2]  = {{ 0 }};
int  R[100001][2] = {{ 0 }};

int solve(vector<node>& graph, int node, int parent, int taken)
{
  if (V[node][taken])
    return R[node][taken];
  
  V[node][taken] = 1;
  
  int result = 0;
  
  
  vector<int>& children = graph[node].children;

  // Non root
  for (auto it = children.begin(); it != children.end(); ++it) {
    if (*it == parent)
      continue;
    if (taken)
      result = result + min(solve(graph, *it, node, 0), solve(graph, *it, node, 1));
    else
      result = result + solve(graph, *it, node, 1);
  }
  result = result + taken;
  R[node][taken] = result;
  //cout << "Solve(" << node << "," << parent << "," << taken << ") = {" << result <<  "}" << endl;
  return result;
}

int main()
{
  int size;
  
  cin >> size;
  V[0][0] = 1;
  V[0][1] = 1;
  
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
  
  cout << min(solve(graph,1, 0, 0), solve(graph,1, 0, 1)) << endl;
  return 0;
}
