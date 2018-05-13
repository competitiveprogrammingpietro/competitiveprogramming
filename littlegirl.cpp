/* 
 * Competitive programming Universita' degli studi di Pisa.
 * Source http://codeforces.com/problemset/problem/313/B?locale=en
 * Complexity O(n)
 */
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;

int64_t compute(vector<int>& array, vector<pair<int, int>>& queries) {
  vector<int64_t> F(array.size(), 0);
  int i, max;
  int64_t sum;
  
  for (i = 0; i < queries.size(); i++) {
    int l = queries[i].first - 1;
    int r = queries[i].second;
    F[l]++;
    if (r < array.size())
      F[r]--;
  }
 
  // Compute frequencies and store them in a sorted data structure
  multiset<int64_t, std::greater<int64_t>> sorted_frequencies;
  sum = F[0];
  sorted_frequencies.insert(F[0]);
  for (i = 1; i < array.size(); ++i) {
    sum += F[i];
    sorted_frequencies.insert(sum);
  }

  // Sort the input array
  sort(array.begin(), array.begin() + array.size(), std::greater<int64_t>());

  // Compute the sum
  sum = max = 0;
  for (auto it = sorted_frequencies.begin(); it != sorted_frequencies.end(); ++it, ++max)
    sum += array[max] * (*it);
  return sum;
}

int main() {
  int i;
  vector<int> array;
  vector<pair<int, int> > queries;
  
  int num_queries, length, item;
  scanf("%d %d", &length, &num_queries);

  for (i = 0; i < length; i++) {
    scanf("%d", &item);
    array.push_back(item);
  }
  
  for (i = 0; i < num_queries; i++) {
    int first, second;
    cin >> first >> second;
    queries.push_back(pair<int, int>(first, second));
  }
  printf("%I64d\n", compute(array, queries));
  return 0;
}

