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
  pair<int64_t, int64_t> coordinates;
  mapping(int index, pair<int64_t, int64_t> elem): index(index), coordinates(elem) { }
};

bool segment_sort(mapping one, mapping two) {
  return one.coordinates.first > two.coordinates.first;
}


int main() {
  int                    i, size;
  vector<mapping>        sorted;
  pair<int64_t, int64_t> item;
  vector<int64_t>        all;
  
  cin >> size;

  all.reserve(size);
  for (i = 0; i < size; i++) { // N
    int64_t a, b;
    
    cin >> a >> b;
    item.first = a;
    item.second = b;
    all.push_back(b);
    sorted.push_back(mapping(i, item));
  }
  
  vector<int>           results(size, 0);
  fenwick_tree<int64_t> ftree(size + 1);

  sort(sorted.begin(), sorted.end(), segment_sort); // lgN
  sort(all.begin(), all.end());                     // lgN

  // Populate the BIT tree
  for (auto it = sorted.begin(); it != sorted.end(); ++it) {
    int i;

    // Look up for the mapping for the right coordinate
    for (i = 0; i < size; i++) {
      if (all[i] == it->coordinates.second)
	break;
    }
    ftree.add(i, 1);
    results[it->index] = ftree.sum(i - 1);       // lgN
  }

  for (auto it = results.begin(); it != results.end(); ++it) {
    cout << *it << endl; 
  }
  return 0;
}

