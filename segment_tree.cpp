#include <vector>
#include <iostream>

#define MIN(a,b)  (a > b) ? a : b 
using namespace std;

class segment_tree {
public:
  segment_tree(int size): m_tree(size * 2 - 1, 0) { };
  void buildTree(vector<int> input, int low, int high, int pos);
  int sum(int qmin, int qmax, int lower, int high, int pos);
  void  update(int i, int delta, int lower, int high, int pos);
  friend ostream& operator<< (ostream& os, const segment_tree& tree);
		    
private:
  vector<int> m_tree;
};


ostream& operator<< (ostream& os, const segment_tree& tree)
{
  for (auto it = tree.m_tree.begin(); it != tree.m_tree.end(); it++) {
    os << *it << ",";
  }
  os << endl;
  return os;
}

void segment_tree::buildTree(vector<int> input, int low, int high, int pos)
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

void  segment_tree::update(int i, int delta, int low, int high, int pos)
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
  
  segment_tree test(4);
  test.update(0, 1, 0, 4, 0);
  test.update(3, 1, 0, 4, 0);
  cout << test << endl;

  cout << test.sum(0, 1, 0, 3, 0) << endl;
  cout << test.sum(0, 3, 0, 3, 0) << endl;
  
}
