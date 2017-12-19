/* Pietro Paolini
 * Competitive programming Universita' degli studi di Pisa.
 * Complexity: O(n^2)
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

  long long x, y, n, count, i;

  n = input.size();
  x = (k - 1)/n;
  y = (k - 1)%n;
  cout << "x" <<  x << endl;
  cout << "y" <<  y << endl;
  if (input[x] != input[x+1]) {
    return Pair(input[x], input[y]);    
  }

  count = 1;
  i = x;
  while (i < input.size() -1 && input[i] == input[i + 1]) {
    count++;
    i++;
  }


  if (y <= count * count)
    return Pair(input[x], input[x]);

  return Pair(input[x], input[y - count*count]);

  
//   // Sort input
//   sort(input.begin(), input.end());

//   if (k == 1)
//     return Pair(*input.begin(), *input.begin());

//   if (k == input.size() * input.size())
//     return Pair(*(input.end()-1), *(input.end()-1));
  
//   Pair last(*input.begin(), *input.begin()), current(0, 0);
//   for (auto it = input.begin(); it != input.end(); ++it) {
//     for (auto inner = input.begin(); inner != input.end(); ++inner) {
//       if (it == input.begin() && inner == input.begin())
// 	continue;

//       current = Pair(*it, *inner);
//       Pair ptr(0, 0);
//       if (current > last || current == last) {
// 	ptr = last;
// 	last = current;
//       }
//       else {
// 	ptr = current;
//       }
// #ifdef DEBUG
//       cout << ptr << endl;
// #endif     
//       if (k == count)
//       	return ptr;
//       count++;
//     }
//   }
//   return Pair(*(input.end()-1), *(input.end()-1));
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
