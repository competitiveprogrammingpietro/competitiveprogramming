#include <iostream>
#include <vector>

/*
 * https://www.spoj.com/problems/PT07X/
 *
 */

using namespace std;
static int N[100][100] = {{ 0 }};
int size;

int f(int node) 
{
  int edge_present = 0;
  vector<int> children;
  
  for (int i = 0; i < size; i++) {
    if (N[node][i] != 0)
      edge_present = 1;

    // Cancel all edges related to me
    children.push_back(i);
    N[node][i] = N[i][node] = 0;
  }

  // There are not edges this node can "serve"
  if (!edge_present)
    return 0;

  // All my edges have been canceled, proceed with children
  int result = 0;
  for (auto it = children.begin();  it != children.end(); ++it) {
    result += f(*it);
  }
  return result + 1;
}

int main()
{
  
  cin >> size;
  for (int i = 0; i < size - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;v--;
    N[u][v] = N[v][u] = 1;
  }

  int res = f(0);
  cout << res << endl;
  return 0;
}
