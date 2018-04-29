/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Souce: http://codeforces.com/contest/86/problem/D
 * Complexity: O(SQRT(N) * N)
 */
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>
#include <map>
#include <cmath>
using namespace std;

class query {
public:
  int l, r, pos;
  bool operator== (const query& one) {
     return one.l == l && one.r == r;
  }
  friend ostream& operator<<(ostream& os, const query& one);
};

ostream& operator<<(ostream& os, const query& one) {
  os << "{" << one.l << "," << one.r << "}";
  return os;
}

bool right_order(const query& one, const query& two) {
  return one.r < two.r;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int                    size_array, num_queries, bucket_size, bucket_number;
  vector<int>            input;
  int64_t                counter[1000000 + 1] = { 0 };
  vector<vector<query> > buckets;;
  vector<int64_t>        results;
  
  cin >> size_array >> num_queries;

  input.reserve(size_array);
  results.reserve(num_queries);
  bucket_size = round((float) (size_array / sqrt(size_array)));
  bucket_number = ceil((float) (size_array / sqrt(size_array)));
  buckets.reserve(bucket_number);
  results.reserve(num_queries);

  for (int i = 0; i < bucket_number; i++) {
    buckets.push_back(vector<query>());
  }
  
  for (int i = 0; i < size_array; i++) {
    int item;
    cin >> item;
    input.push_back(item);
  }

  // Store all queries in the buckets
  for (int i = 0; i < num_queries; i++) { // O(Q * lgQ)
    query query;
    int bucket;
    cin >> query.l;
    cin >> query.r;
    query.pos = i;
    bucket = (query.l - 1) / bucket_size;
    buckets[bucket].push_back(query);
  }

  int r, l;
  int64_t result;
  r = -1;
  l = 0;
  result = 0;
  for (auto bucket = buckets.begin(); bucket != buckets.end(); ++bucket) { // O(SQRT(N) * N)
    sort (bucket->begin(), bucket->end(), right_order);                    // O(SQRT(N)* LG(SQRT(N)))
    for (auto query_item = bucket->begin(); query_item != bucket->end(); ++query_item) {
      int query_l, query_r;
      
      // Query's boundaries
      query_l = query_item->l - 1;
      query_r = query_item->r - 1;
      while (l < query_l) {
	counter[input[l]]--;
	result += input[l] * (1 - ((counter[input[l]] + 1) << 1));
	l++;
      }
      while (l > query_l) {
	l--;
	counter[input[l]]++;
	result += input[l] * ((counter[input[l]] << 1) - 1);
      }
      while(r < query_r) {
	r++;
	counter[input[r]]++;
	result += input[r] * ((counter[input[r]] << 1) - 1);
      }
      while(r > query_r) {
	counter[input[r]]--;
	result += input[r] * (1 - ((counter[input[r]] + 1) << 1));
	r--;
      }
      results[query_item->pos] = result;
    }
  }
  for (auto i = 0; i < num_queries; ++i) { // O(Q) Q = queries
    cout << results[i] << endl;
  }
  return 0;
}
