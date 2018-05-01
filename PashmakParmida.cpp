/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(NlgN)
 * Source: http://codeforces.com/problemset/problem/459/D?locale=en
 */
#include <iostream>
#include <vector>
#include <algorithm>

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

using namespace std;


int main() {
  int size, i;
  vector<int> input;

  cin >> size;
  input.reserve(size);
  for (i = 0; i < size; i++) {
    int item;
    cin >> item;
    input.push_back(item);
  }

  // Sort the array
  sort(input.begin(), input.end());
  // for (auto it = input.begin(); it != input.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;

  // Compute the rank
  int rank = 1;
  i = 0;
  vector<int> mapped(size, 0);
  for (auto it = input.begin(); it != input.end() - 1; ++it, ++i) {
    mapped[i] = rank;
    if (*it != *(it + 1))
      rank++;
  }
  mapped[size -1] = rank;
  
  // for (auto it = mapped.begin(); it != mapped.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;
  
  // Compute the suffix and BIT
  fenwick_tree<int> tree(size);
  vector<int> suffix(size, 0), counters(size, 0);
  for (i = size - 1; i >= 0; --i) {
    counters[mapped[i]]++;
    suffix[i] = counters[mapped[i]];
    tree.add(suffix[i], 1);
  }
  
  // for (auto it = suffix.begin(); it != suffix.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;
  //TODO: da rivedere
  fill(counters.begin(), counters.end(), 0);
  int result = 0;
  for (int i = 0; i < size; ++i) {
    tree.add(suffix[i], -1);
    counters[mapped[i]]++;
    result += tree.sum(counters[mapped[i]] - 1);
  }
  cout << result << endl;
  
}