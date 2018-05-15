/*
 * Competive Programming - UniPi.
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
  int64_t size, i;
  vector<int64_t> input, map;

  size = 0;
  cin >> size;
  
  input.reserve(size);
  map.reserve(size);
  for (i = 0; i < size; i++) {
    int64_t item;
    cin >> item;
    input.push_back(item);
    map.push_back(item);
  }

  // Sort the array
  sort(map.begin(), map.end());

  // for (auto it = map.begin(); it != map.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;

  // strip off duplicates and resize
  map.resize(distance(map.begin(),  unique(map.begin(), map.end())));

  for (auto &elem : input) {
    elem = distance(map.begin(), lower_bound(map.begin(), map.end(), elem));
    // cout << elem << endl;
  }
  
  // for (auto it = input.begin(); it != input.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;


  // Compute the suffix and BIT
  fenwick_tree<int64_t> tree(size);
  vector<int64_t> suffix(size, 0), counters(size + 1, 0), prefix(size, 0);

  for (i = size - 1; i >= 0; --i) {
    counters[input[i]]++;
    suffix[i] = counters[input[i]];
    tree.add(suffix[i], 1);
  }
  
  fill(counters.begin(), counters.end(), 0);
  for (i = 0; i < size; i++) {
    counters[input[i]]++;
    prefix[i] = counters[input[i]];
  }

  // for (int j = 0; j < size; j++) {
  //   cout << prefix[j] << ",";
  // }
  // cout << endl;
    
  // for (int j = 0 ; j < size; j++) {
  //   cout << suffix[j] << ",";
  // }
  // cout << endl;


  // cout << endl;
  fill(counters.begin(), counters.end(), 0);
  int64_t result = 0;
  for (int i = 0; i < size; ++i) {
    int64_t first_interval, second_interval;
    
    first_interval = prefix[i];
    // cout << "first interval " << first_interval << endl; 
    tree.add(suffix[i], -1); 
    second_interval = first_interval - 1 > 0 ? tree.sum(first_interval - 1) : 0;
    // cout << "second interval " << second_interval << endl;
    //tree.add(suffix[i], 1); 
    result += second_interval;
  }
  printf("%I64d\n", result);
  return 0;
}
