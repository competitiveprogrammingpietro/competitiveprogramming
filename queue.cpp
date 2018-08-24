#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// Source: http://codeforces.com/problemset/problem/141/C?locale=en
/* 
  Code from https://github.com/spaghetti-source/algorithm/blob/master/data_structure/fenwick_tree.cc
 */
 
#include <vector>

template <class T>
struct fenwick_tree {
  std::vector<T> x;
  fenwick_tree(size_t n) : x(n+1) { } 
  
  // initialize by a constant
  fenwick_tree(size_t n, T a) : x(n+1, a) { 
    x[0] = 0;
    for (int k = 1; k+(k&-k) <= n; ++k) x[k+(k&-k)] += x[k];
  }
   
  // initialize by a std::vector
  fenwick_tree(std::vector<T> y) : x(y.size()+1) {
    for (int k = 0; k < y.size(); ++k) x[k+1] = y[k];
    for (int k = 1; k+(k&-k) < x.size(); ++k) x[k+(k&-k)] += x[k];
  }
  
  // b[k] += a
  void add(int k, T a) { 
    for (++k; k < x.size(); k += k&-k) x[k] += a;
  }
  
  // sum b[0,k)
  T sum(int k) {
    T s = 0;
    for (++k; k > 0; k &= k-1) s += x[k];
    return s;
  }
  
  // min { k : sum(k) >= a }; it requires b[k] >= 0
  int lower_bound(T a) {
    if (a <= 0) return 0;
    int k = x.size()-1; 
    for (int s: {1,2,4,8,16}) k |= (k >> s); 
    for (int p = ++k; p > 0; p >>= 1, k |= p)
      if (k < x.size() && x[k] < a) a -= x[k]; else k ^= p;
    return k+1;
  }
  
  // max { k : sum(k) <= a }; it requires b[k] >= 0
  int upper_bound(T a) {
    int k = x.size()-1; 
    for (int s: {1,2,4,8,16}) k |= (k >> s); 
    for (int p = ++k; p > 0; p >>= 1, k |= p)
      if (k < x.size() && x[k] <= a) a -= x[k]; else k ^= p;
    return k;
  }
};


class item {
public:
  int index;
  string name;
  int a;
  int height;
};

bool sort_item(item one, item two) {
  return one.a < two.a;
}

bool sort_pair(pair<string, int> one, pair<string, int> two)
{
  return one.second < two.second;
}

int main()
{
  int size, i;

  cin >> size;
  vector<item> input(size);

  for (i = 0; i < size; i++) {
    cin >> input[i].name >> input[i].a;
    input[i].index = i;
  }

  sort(input.begin(), input.end(), sort_pair);
  for (i = 0; i < size; i++) {
    cout << "input[" << i << "]=" << input[i].a << "," << input[i].name << endl;
  }

  // Check if an answer exists
  for (i = 0; i < size; i++) {
    if (input[i].a > i) {
      cout << "-1" << endl;
      return 0;
    }
  }

  vector<int> output(size, -1);

  for (i = 0; i < size; i++) {
    int j = input[i].second;
    cout << "j=" << j << endl;
    while (output[j] != -1)
      j++;
    cout << "output[" << j << "]=" << input[input[i].index].name << endl;
    output[j] = input[i].index;
  }

  int base = 150;
  for (i = 0; i < size; i++) {
    cout << i << "=" << output[i] << " " << base << endl;
    base += 10;
  }
  
  return 0;
}
