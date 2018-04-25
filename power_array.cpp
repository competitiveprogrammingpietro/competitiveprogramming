/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Souce: http://codeforces.com/contest/86/problem/D
 * Complexity: O(N * lgN)
 */
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

class query {
public:
  int l, r, pos;
  bool operator< (const query& one) const {
    if (l == one.l)
      return r < one.r;
    else
      return l < one.l;
  }
  bool operator== (const query& one) {
     return one.l == l && one.r == r;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int size_array, num_queries;
  vector<int> input;

  cin >> size_array >> num_queries;
  input.reserve(size_array);
  for (int i = 0; i < size_array; i++) {
    int item;
    cin >> item;
    input.push_back(item);
  }

  int64_t         counter[1000000] = { 0 };
  vector<int>     result_array;
  multiset<query> queries;
  vector<int64_t> results(num_queries, 0);

  // Store all queries
  for (int i = 0; i < num_queries; i++) { // O(Q * lgQ)
    query query;
    cin >> query.l;
    cin >> query.r;
    query.pos = i;
    queries.insert(query);
  }

  int r, l;
  r = -1;
  l = 0;
  for (auto it = queries.begin(); it != queries.end(); ++it) { // O(SQRT(N) * N)
    int query_l, query_r;

    // Query's boundaries
    query_l = it->l;
    query_r = it->r;
    query_l--;
    query_r--;
    while (l < query_l) {
      counter[input[l]]--;
      l++;
    }
    while (l > query_l) {
      counter[input[l]]++;
      l--;
    }
    while(r < query_r) {
      r++;
      counter[input[r]]++;
    }
    while(r > query_r) {
      counter[input[r]]--;
      r--;
    }

    int64_t result = 0;
    for (int x = query_l; x <= query_r; x++) {
      result += input[x] * counter[input[x]] ;//* counter[input[x]];
    }
    results[it->pos] = result;
  }

  for (auto it = results.begin(); it != results.end(); ++it) { // O(Q) Q = queries
    cout << *it << endl;
  }
  return 0;
}
