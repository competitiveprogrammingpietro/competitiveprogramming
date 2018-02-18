/* Pietro Paolini
 * Competitive programming Universita' degli studi di Pisa.
 * Source http://codeforces.com/problemset/problem/313/B?locale=en
 * Complexity O(n)
 */
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<int> resolve_queries(string& input, vector<pair<int, int>>& queries) {
  int B[input.size()], i;
  int SUM[input.size() + 1];
  
  vector<int> output;
  
  // Build array of counters
  for ( i = 0; i < input.size() -1; i++) {
    if (input[i] == input[i + 1])
      B[i] = 1;
    else
      B[i] = 0;
  }

  // Last element's value is zero
  B[input.size() - 1] = 0;

  // Compute the prefix sum
  SUM[0] = 0;
  for (i = 1; i < input.size(); ++i) {
    SUM[i] = B[i - 1] + SUM[i -1];
  }
  SUM[input.size()] = SUM[input.size() - 1]; // Last element in B is always zero
  
  
  // "Resolve" each query
  for (auto it = queries.begin(); it != queries.end(); ++it) {
    pair<int, int> item = *it;
    output.push_back(SUM[item.second - 1] - SUM[item.first - 1]);
  }
  return output;
}

int main() {
  string S;
  int num_queries, i;
  vector<pair<int, int>> queries;
  vector<int> result;
  getline(cin, S);
  cin >> num_queries;
  for (i = 0; i < num_queries; i++) {
    int first, second;
    cin >> first >> second;
    queries.push_back(pair<int, int>(first, second));
  }
  result = resolve_queries(S, queries);
  for (auto it = result.begin() ; it != result.end(); ++it) {
    cout << *it << endl;
  }
  return 0;
}

