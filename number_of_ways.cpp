/* Pietro Paolini
 * Competitive programming Universita' degli studi di Pisa.
 * Complexity: O(n^2)
 * Source: http://codeforces.com/problemset/problem/160
 */

#include<vector>
#include<iostream>

using namespace std;

int ways(vector<int>& input) {
  int SUM[input.size()], C[input.size()];
  int i, j, target, max;

  SUM[0] = input[0];
  for (i = 1; i < input.size(); ++i) {
    SUM[i] = SUM[i - 1] + input[i];
  }
  max = SUM[input.size() - 1];
  
  // There is no solution
  if (max % 3 != 0)
    return 0;
  target = max / 3; // Max divided by three

  // Compute C
  for (i = 0; i < input.size(); ++i) {
    int sum, acc;
    sum = acc = 0;
    for (j = input.size() - 1; j >= i; --j) {
      sum += input[j];
      if (sum == target)
	acc++;
    }
    C[i] = acc;
  }
  int result = 0;
  for (i = 0; i < input.size(); ++i) {

    // No further solutions possible
    if (i + 2 > input.size() - 1)
      return result;

    // Not target
    if (SUM[i] != target)
      continue;

    // Solution found
    result += C[i + 2];
  }
  return result;
}

int main() {
  int size, i;
  vector<int> input;
  cin >> size;
  for (i = 0; i < size; i++) {
    int item;
    cin >> item;
    input.push_back(item);
  }
  cout << ways(input) << endl;
  return 0;
}
