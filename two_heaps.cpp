/**
 * Source : http://codeforces.com/problemset/problem/353/B?locale=en
 * Complexity : O(lgN)
 *
 */

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct ITEM {
  int value, index;
};

bool sort_by_value(ITEM one, ITEM two)
{
  return one.value > two.value;
}

int main()
{
  int n, size;
  std::ios_base::sync_with_stdio(false);
  cin >> size;

  n = size * 2;
  vector<ITEM> input(n);
  vector<int> result(n, 0);
  for (int i = 0; i < n; i++) {
    ITEM item;
    cin >> item.value;
    item.index = i;
    input[i] = item;
  }

  sort(input.begin(), input.end(), sort_by_value);

  int heap, clones;

  heap = clones = 0;
  
  for (auto it = input.begin(); it != input.end(); ++it) {
    result[it->index] = (heap++ % 2);
  }

  cout << (size * size) << endl;

  for (auto i = 0; i < n; i++) {
    cout << result[i] + 1 << " ";
  }
  cout << endl;

  return 0;
}
