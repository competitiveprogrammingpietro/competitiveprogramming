/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Souce: http://codeforces.com/contest/86/problem/D
 * Complexity: O(mn)
 */
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;


int main() {
  int64_t size_array, num_queries;
  vector<int64_t> input;

  cin >> size_array >> num_queries;
  input.reserve(size_array);
  for (int64_t i = 0; i < size_array; i++) {
    int64_t item;
    cin >> item;
    input.push_back(item);
  }

  vector<int64_t> counter(size_array + 1, 0);
  vector<int64_t> result_array;
  int64_t r, l;
  r = l = 0;
  for (int64_t i = 0; i < num_queries; i++) {
    int64_t query_l, query_r;
    
    // Query's boundaries
    cin >> query_l;
    cin >> query_r;
    while (l < query_l) {
      l++;
      counter[input[l - 1]]--;
     }
    while (l >= query_l) {
      counter[input[l - 1]]++;
      l--;
    }
    while(r <= query_r) {
      r++;
      counter[input[r - 1]]++;
    }
    while(r > query_r) {
      counter[input[r - 1]]--;
      r--;
    }
    
    int64_t result = 0;
    for (auto it = counter.begin(); it != counter.end(); ++it) {
      if (*it == 0)
	continue;
      result += (counter.size() - (counter.end() - it)) * (*it) * (*it);
    }
    result_array.push_back(result);
  }

  for (auto it = result_array.begin(); it != result_array.end(); ++it) {
    cout << *it << endl;
  }
  return 0;
}
