#import <iostream>
#import <vector>
#import <cstdlib>

/*
 * Source: https://www.spoj.com/submit/CHAIN/
 * TODO: works well locally get SIGABRT on Spoj (c++ vs g++)
 * Complexity: O(n)
 */
using namespace std;
int compute_distance(vector<int> predecessor, vector<int> distance, int node)
{

  // Distance from myself
  if (predecessor[node] == node)
    return 0;

  // Distance already computed
  if (distance[predecessor[node]] != 0)
    return 1 + distance[predecessor[node]];

  // Recursive step
  return 1 + compute_distance(predecessor, distance, predecessor[node]);
}

int main()
{
  int test, nodes, hints, result;

  cin >> test;

  for (int i = 0; i < test; i++) {
    cin >> nodes >> hints;

    nodes += 1; // Start counting from 1
    result = 0;
    vector<int> predecessor(nodes), distance(nodes, 0);

    for (int j = 1; j < nodes; j++)
      predecessor[j] = j;
      
    for (int j = 0; j < hints; j++) {
      int type, x, y;

      cin >> type >> x >> y;

      if (x > nodes || y > nodes)
	result++;

      distance[x] = (distance[x] == 0) ? compute_distance(predecessor, distance, x) : distance[x];
      distance[y] = (distance[y] == 0) ? compute_distance(predecessor, distance, y) : distance[y];

      if (distance[x] == 0 || distance[y] == 0) {
	predecessor[y] = x;
	continue;
      }

      // Distance module must be one for eating, zero for animals having the same type
      int mod_distance_res = (type == 2) ? 1 : 0;
      int mod_distance_cmp = abs(distance[x] - distance[y]) % 3;

      if (mod_distance_res != mod_distance_cmp) {
	result++;
	continue;
      }

      // Add eat link if it is all OK
      if (type == 2) {
	predecessor[y] = x;
      }
    }

    cout << result << endl;
  }
}

