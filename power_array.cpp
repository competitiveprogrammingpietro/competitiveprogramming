/*
 * Competive Programming - UniPi.
 * Souce: http://codeforces.com/contest/86/problem/D
 * Complexity: O(SQRT(N) * N)
 */
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>
#include <map>
#include <cmath>
#define MAX_LENGTH  (200000 + 5)
#define MAX_COLORS (1000000 + 5)
using namespace std;

class query {
public:
  int l, r, pos;
  //  friend ostream& operator<<(ostream& os, const query& one);
};

// ostream& operator<<(ostream& os, const query& one) {
//   os << "{" << one.l << "," << one.r << "}";
//   return os;
// }

int bucket_size;
long long  counter[MAX_COLORS] = { 0 };
int input[MAX_LENGTH] = { 0 };
query Q[MAX_LENGTH];
long long results[MAX_LENGTH] = { 0 };
		 

bool right_order(query one, query two) {
  if ((one.l / bucket_size) == (two.l / bucket_size))
    return one.r < two.r;
  else
    return (one.l) < (two.l);
}

int main() {
  // std::ios_base::sync_with_stdio(false);
  // cin.tie(0);
  int                    size_array, num_queries;
  
  //  cin >> size_array >> num_queries;
  scanf("%d %d", &size_array, &num_queries);

  bucket_size = round((float) (size_array / sqrt(size_array)));
  for (int i = 0; i < size_array; i++) {
    scanf("%d", &input[i]);
	  //    cin >> input[i];
  }

  // Store all queries in the buckets
  for (int i = 0; i < num_queries; i++) { // O(Q * lgQ)
    // cin >>  Q[i].l;
    // cin >>  Q[i].r;
    scanf("%d %d", &Q[i].l, &Q[i].r);
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

      //      cout << Q[i] << endl;
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
    printf("%I64d\n", results[i]);
    //cout << results[i] << '\n';
  }
  return 0;
}
