#include <iostream>
#include <vector>
#include <utility>

/*
 * https://www.spoj.com/problems/PT07X/
 * Complexity O(V + E)
 * TODO: not quite clear why it does not pass last case
 * http://discuss.spoj.com/t/vertex-cover/30039 
 */

using namespace std;


int main()
{
  int size;
  vector<int> nodes;
  int** N;
  int *V;
  
  cin >> size;

  if (size == 1) {
    cout << 1 << endl;
    return 0;
  }
  N = new int*[size + 1]();
  V = new int[size + 1]();
  
  for (int i = 1; i < size + 1; i++) {
    N[i] = new int[size + 1]();
    V[i] = false;
  }
  for (int i = 0; i < size - 1; i++) {
    int u, v;
    cin >> u >> v;
    N[u][v] = 1;
    N[v][u] = 1;
    //    cout << "(" << u << "," << v << ")" << N[v][u] << endl;// Sth wrong here 
  }

  // for (int i = 1; i < size + 1; i++) {
  //   for (int j = 0; j < size + 1; j++) {
  //     cout << N[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  //  cout << "-----" << endl;
  for (int i = 1; i < size + 1; i++) {

    if (V[i])
      continue;
    
    // Pick the first edge up and remove all the incident edges
    for (int j = 1; j < size + 1; j++) {

      if (N[i][j] == 0)
	continue;

      if (V[j]) 
	continue;

      //      cout << "Examining " << i << "," << j << endl;
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
    // cout << "-------------------" << endl;
    // for (int i = 1; i < size + 1; i++) {
    //   for (int j = 0; j < size + 1; j++) {
    // 	cout << N[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    // cout << "-------------------" << endl;
  }
  cout << nodes.size() << endl;
  return 0;
}
