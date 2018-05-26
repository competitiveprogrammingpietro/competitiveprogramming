/* 
 * Competitive programming Universita' degli studi di Pisa.
 * Complexity: O(n^2)
 * Source: http://codeforces.com/problemset/problem/160
 */

#include<vector>
#include<iostream>

using namespace std;

int64_t ways(vector<int>& input) {
  int64_t n, i;
  int64_t sum, S;
  int64_t C[input.size()] = { 0 };
  int64_t result;
  S = 0;
  for (i = 0; i < input.size(); ++i) {
    S += input[i];
    C[i] = 0;
  }

  // There is no solution
  if (S % 3 != 0)
    return 0;
  S = S / 3;

  // Compute C
  n = input.size();
  sum = input[n - 1];
  C[n-1] = (input[n-1] == S) ? 1 : 0;
  for (i = n - 2; i>=0; i--) {
    C[i] = C[i + 1];
    sum += input[i];
    if (sum == S)
      C[i] += 1;
  }

  result = sum = 0;
  for (i = 0; i < input.size() - 2; ++i) {
    sum += input[i];
    
    // Not target
    if (sum != S)
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
