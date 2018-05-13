/*
 * Competive Programming - UniPi.
 * Complexity : O(NlgN)
 * Source: http://www.spoj.com/submit/INVCNT/
 */
#include <iostream>
#include <vector>

#pragma once
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
  int tests, size, updates;
  std::ios_base::sync_with_stdio(false);
  cin >> tests;

  for (int i = 0; i < tests; i++) {
    scanf("%d %d", &size, &updates);
    fenwick_tree<int64_t> tree(size + 1, 0);

    // Build the tree
    for (int j = 0; j < updates; j++) {
      int l, r, v;
      scanf("%u%d%d", &l, &r, &v);
      tree.add(l, v);
      tree.add(r + 1, -1 * v);
    }

    // Get and answer queries
    int queries;
    scanf("%d", &queries);
    for (int i = 0; i < queries; i++) {
      int index;
      scanf("%d", &index);
      printf("%I64d\n", tree.sum(index));
    }
  }  

}
