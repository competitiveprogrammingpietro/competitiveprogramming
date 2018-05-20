/*
 * Competive Programming - UniPi.
 * Complexity : O(NlgN)
 * Source: http://codeforces.com/problemset/problem/459/D?locale=en
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


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
    //    cout << elem << endl;
  }
  
  // for (auto it = input.begin(); it != input.end(); ++it) {
  //   cout << *it << ",";
  // }
  // cout << endl;


  // Compute the suffix and BIT
  segment_tree tree(size);
  vector<int64_t> suffix(size, 0), counters(size + 1, 0), prefix(size, 0);

  for (i = size - 1; i >= 0; --i) {
    counters[input[i]]++;
    suffix[i] = counters[input[i]];
    tree.update(suffix[i], 1, 0, size, 0);
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


  //  cout << endl;
  fill(counters.begin(), counters.end(), 0);
  int64_t result = 0;
  for (int i = 0; i < size; ++i) {
    int64_t first_interval, second_interval;
    
    first_interval = prefix[i];
    tree.update(suffix[i], -1, 0, size, 0); 
    second_interval = first_interval - 1 > 0 ? tree.sum(0, first_interval - 1, 0, size, 0) : 0;
    result += second_interval;
  }
  printf("%I64d\n", result);
  return 0;
}
