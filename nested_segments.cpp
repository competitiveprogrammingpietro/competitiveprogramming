/* Pietro Paolini
 * Competitive programming Universita' degli studi di Pisa.
 * Source http://codeforces.com/problemset/problem/652/D?locale=en
 * Complexity O(NlgN)
 */
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;

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

struct mapping {
  int index;
  pair<int64_t, int64_t> item;
  mapping(int index, pair<int64_t, int64_t> elem): index(index), item(elem) { }
};

bool segment_sort(mapping one, mapping two) {
  return one.item.first > two.item.first;
}

bool index_sort(mapping one, mapping two) {
  return one.index < two.index;
}

int main() {
  int i, size, max;
  vector<mapping> sorted;
  pair<int64_t, int64_t> item;
  
  cin >> size;

  max = 0;
  for (i = 0; i < size; i++) { // N
    cin >> item.first >> item.second;
    max = (item.second > max ) ? item.second : max;
    sorted.push_back(mapping(i, item));
  }
  
  // Cough cough ... test wants input to be consumed
  if (size == 1) {
    cout << 0 << endl;
    return 0;
  }

  fenwick_tree<int64_t> ftree(max + 1, 0);
  vector<int> results(size, 0);

  sort(sorted.begin(), sorted.end(), segment_sort); // lgN

  // Populate the BIT tree
  for (auto it = sorted.begin(); it != sorted.end(); ++it) {
    ftree.add(it->item.second, 1);
    results[it->index] = ftree.sum(it->item.second);
  }

  for (auto it = results.begin(); it != results.end(); ++it) {
    cout << *it - 1 << endl; // Why minus one needed ?
  }
  return 0;
}
