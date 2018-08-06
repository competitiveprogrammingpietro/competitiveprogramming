#include <iostream>
#include <vector>
using namespace std;

int binary_search(vector<int>& A, int l, int r, int key)
{
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    if (A[m] >= key)
      r = m;
    else
      l = m;
  }
  return r;
}

int test()
{
  int size, next;

  cin >> size;

  if (size == 0)
    return 0;
  
  vector<int> input(size), ends(size, 0);

  for (int i = 0; i < size; i++) {
    cin >> input[i];
  }

  ends[0] = input[0];
  next = 1;
  for (int i = 1; i < size; i++) {
    if (input[i] < ends[0]) {
      ends[0] = input[i];
    }
    else if (ends[next - 1] < input[i]) {
      ends[next++] = input[i];
    } else {
      ends[binary_search(ends, -1, next - 1, input[i])] = input[i];
    }
  }
  return next;
}

int main()
{
  int tests;

  cin >> tests;

  for (int i = 0; i < tests; i++)
    cout << test() << endl;

  return 0;
}
