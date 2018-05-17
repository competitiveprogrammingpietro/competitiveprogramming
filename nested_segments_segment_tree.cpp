/* 
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
#define MIN(a,b)  (a > b) ? a : b 

class segment_tree {
public:
  segment_tree(int size);
  void buildTree(vector<int64_t> input, int low, int high, int pos);
  int sum(int qmin, int qmax, int lower, int high, int pos);
  void  update(int i, int64_t delta, int lower, int high, int pos);
  friend ostream& operator<< (ostream& os, const segment_tree& tree);
		    
private:
  vector<int64_t> m_tree;
};


ostream& operator<< (ostream& os, const segment_tree& tree)
{
  for (auto it = tree.m_tree.begin(); it != tree.m_tree.end(); it++) {
    os << *it << ",";
  }
  os << endl;
  return os;
}

segment_tree::segment_tree(int size) {
    int x = (int)(ceil(log2(size))); 
    int max_size = 2*(int)pow(2, x) - 1;
    m_tree.reserve(max_size);
    m_tree.assign(max_size, 0);
}

void segment_tree::buildTree(vector<int64_t> input, int low, int high, int pos)
{
  if (low == high) {
    m_tree[pos] = input[low];
    return;
  }

  int middle = (low + high) / 2;
  buildTree(input, low, middle, pos * 2 + 1);
  buildTree(input, middle, high, pos * 2 + 2);
  m_tree[pos] = m_tree[2 * pos  + 1] + m_tree[2 * pos + 2];
  return;
}

int segment_tree::sum(int qmin, int qmax, int low, int high, int pos)
{
  if (qmin <= low && qmax >= high)
    return m_tree[pos];

  if (qmin > high || qmax < low)
    return 0;

  int middle = (low + high) / 2;
  return sum(qmin, qmax, middle + 1, high, pos * 2 + 2) +
         sum(qmin, qmax, low, middle, pos * 2 + 1);
}

void  segment_tree::update(int i, int64_t delta, int low, int high, int pos)
{
  if (i > high || i < low)
    return;

  // Leaf
  if (high == low) {
    m_tree[pos] += delta;
    return;
  }

  int middle = (low + high) / 2;
  update(i, delta, low, middle, pos * 2 + 1);
  update(i, delta, middle + 1, high, pos * 2 + 2);
  m_tree[pos] = m_tree[pos * 2 + 1] + m_tree[pos * 2 + 2];
  return;
}

struct mapping {
  int index;
  pair<int64_t, int64_t> coordinates;
  mapping(int index, pair<int64_t, int64_t> elem): index(index), coordinates(elem) { }
  friend ostream& operator <<(ostream& out, const mapping& one);
};

ostream& operator <<(ostream& out, mapping& one) {
  out << "{" << one.coordinates.first << "," << one.coordinates.second << "}";
  return out;
}

bool segment_sort(mapping one, mapping two) {
  return one.coordinates.first > two.coordinates.first;
}

bool right_sort(mapping one, mapping two) {
  return one.coordinates.second < two.coordinates.second;
}


int main() {
  int                    i, size;
  vector<mapping>        sorted;
  pair<int64_t, int64_t> item;
  vector<int64_t>        all;
  
  cin >> size;

  all.reserve(size * 2);
  for (i = 0; i < size; i++) { // N
    int64_t a, b;
    
    cin >> a >> b;
    item.first = a;
    item.second = b;
    all.push_back(a);
    all.push_back(b);
    sorted.push_back(mapping(i, item));
  }
  
  vector<int>           results(size, 0);
  segment_tree          tree(size * 2 + 1);


  sort(all.begin(), all.end());
  
  for (auto it = sorted.begin(); it != sorted.end(); ++it) { // lgN
    //    cout  << (int64_t) (lower_bound(all.begin(), all.end(), it->coordinates.first) - all.begin()) << ", " << (int64_t) (lower_bound(all.begin(), all.end(), it->coordinates.second) - all.begin()) << endl;
    it->coordinates.first = (int64_t) (lower_bound(all.begin(), all.end(), it->coordinates.first) - all.begin());
    it->coordinates.second = (int64_t) (lower_bound(all.begin(), all.end(), it->coordinates.second) - all.begin());
  }

  sort(sorted.begin(), sorted.end(), segment_sort); // lgN
    
  // Populate the BIT tree
  for (auto it = sorted.begin(); it != sorted.end(); ++it) {
    //    cout << *it << endl;
    tree.update(it->coordinates.second, 1, 0, size * 2, 0);
    //    cout << tree << endl;
    results[it->index] = tree.sum(0, it->coordinates.second - 1, 0, size * 2, 0);
  }

  for (auto it = results.begin(); it != results.end(); ++it) {
    printf("%I64d\n", *it); 
  }
  return 0;
}

