/* Pietro Paolini
 * Competitive programming Universita' degli studi di Pisa.
 * Complexity: O(lgN)
 * Source: http://codeforces.com/problemset/problem/160/C?locale=en
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Pair {
public:
  long long first, second;
  Pair(long long one, long long two):first(one), second(two) { }
  friend bool operator < (Pair const& a, Pair const& b);
  friend bool operator > (Pair const& a, Pair const& b);
  friend bool operator == (Pair const& a, Pair const& b);
  friend bool operator != (Pair const& a, Pair const& b);
  friend ostream& operator << (ostream& os, const Pair& obj);
};

bool operator < (Pair const& a, Pair const& b) {
  if (a.first < b.first)
    return true;
  if (a.first == b.first && a.second < b.second) {
    return true;
  }
  return false;
}

bool operator > (Pair const& a, Pair const& b) {
  if (a.first > b.first)
    return true;
  if (a.first == b.first && a.second > b.second) {
    return true;
  }
  return false;
}

bool operator == (Pair const& a, Pair const& b) {
  if (a.first == b.first && a.second == b.second)
    return true;
  return false;
}

bool operator != (Pair const& a, Pair const& b) {
  if (a.first != b.first || a.second != b.second)
    return true;
  return false;
}

ostream& operator << (ostream& os, const Pair& obj) {
  cout << obj.first << " " << obj.second;
  return os;
}



Pair find_pair(vector<int>& input, long long k) {

 // Sort input
  sort(input.begin(), input.end());

  long long x, y, n, r, i;

  n = input.size();
  x = (k - 1)/n;
  y = (k - 1)%n;
  
  r = count(input.begin(), input.end(), input[x]);
  i = 0;
  while (i < n) {
    if (input[i] == input[x])
      break;
    i++;
  }
  y = ((k - 1) - i * n) / r;
  return Pair(input[x], input[y]);
}

int main() {

  long long n, k, i, a, count;
  vector<int> input;
  cin >> n >> k;
  for (i = 0; i < n; i++) {
    cin >> a;
    input.push_back(a);
  }
  Pair output = find_pair(input, k);
  cout << output << endl;
  return 0;
}
