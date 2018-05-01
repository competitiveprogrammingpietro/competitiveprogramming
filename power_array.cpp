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
  friend ostream& operator<<(ostream& os, const query& one);
};

ostream& operator<<(ostream& os, const query& one) {
  os << "{" << one.l << "," << one.r << "}";
  return os;
}

int bucket_size;
long long  counter[1000000 + 1] = { 0 };
int input[200000 + 2] = { 0 };
query Q[200000 + 2] = { 0 };
bool right_order(query one, query two) {
  if ((one.l / bucket_size) < (two.l / bucket_size))
    return true;
  else if ((one.l / bucket_size) > (two.l / bucket_size))
    return false;
  else
    return one.r < two.r;
}



int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  int                    size_array, num_queries;
  vector<long long>      results;
  
  cin >> size_array >> num_queries;
  bucket_size = round((float) (size_array / sqrt(size_array)));
  results.reserve(num_queries + 1);
  for (int i = 0; i < size_array; i++) {
    cin >> input[i];
  }

  // Store all queries in the buckets
  for (int i = 0; i < num_queries; i++) { // O(Q * lgQ)
    cin >>  Q[i].l;
    cin >>  Q[i].r;
    Q[i].pos = i;
  }

  int r, l;
  long long result;
  r = -1;
  l = 0;
  result = 0;
  sort (Q, Q + num_queries, right_order);// O(SQRT(N)* LG(SQRT(N)))
  for (int i = 0; i < num_queries; i++) {
      int query_l, query_r;
      
      // Query's boundaries
      query_l = Q[i].l - 1;
      query_r = Q[i].r - 1;

      while (l < query_l) {
	counter[input[l]]--;
	result -= 2 * input[l] * counter[input[l]] + input[l];
	l++;
      }
      while (l > query_l) {
	l--;
	result += 2 * input[l] * counter[input[l]] + input[l];
	counter[input[l]]++;
      }
      while(r < query_r) {
	r++;
	result += 2 * input[r] * counter[input[r]] + input[r];
	counter[input[r]]++;
      }
      while(r > query_r) {
	counter[input[r]]--;
	result -= 2 * input[r] * counter[input[r]] + input[r];
	r--;
      }
      results[Q[i].pos] = result;
    }
  for (auto i = 0; i < num_queries; ++i) { // O(Q) Q = queries
    cout << results[i] << endl;
  }
  return 0;
}
