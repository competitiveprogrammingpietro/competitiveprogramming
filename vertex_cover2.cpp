#include <iostream>
#include <vector>
#include <utility>

/*
 * TODO: Ask professor
 * https://www.spoj.com/problems/PT07X/
 * Complexity O(V + E)
 */

using namespace std;


int main()
{
  int size;
  vector<int> nodes;
  int** N;
  int *V;
  
  cin >> size;
  N = new int*[size + 1]();
  V = new int[size + 1]();
  
  for (int i = 1; i < size + 1; i++) {
    N[i] = new int[size + 1]();
  }
  for (int i = 0; i < size - 1; i++) {
    int u, v;
    cin >> u >> v;
    N[u][v] = N[v][u] = 1;
    //    cout << "(" << u << "," << v << ")" << N[u][v] << endl;
  }

  //  cout << "-----" << endl;
  for (int i = 1; i < size + 1; i++) {

    if (V[i])
      continue;
    
    // Pick the first edge up and remove all the incident edges
    for (int j = 1; j < size + 1; j++) {
      //      cout << "(" << i << "," << j << ")" << N[i][j] << endl;

      if (N[i][j] == 0)
	continue;

      if (V[j])
	continue;

      nodes.push_back(i);
      nodes.push_back(j);
      
      V[i] = V[j] = 1;
      for (int z = 1; z < size + 1; z++) {

	// Columns
	N[z][i] = N[z][j] = 0;

	//Rows
	N[i][z] = N[j][z] = 0;
      }
    }
  }
  //  cout << "-----" << endl;
  cout << nodes.size() << endl;
  return 0;
}
