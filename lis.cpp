#include <iostream>
#include <vector>
using namespace std;

int LIS(vector<int>& S, int i)
{
  if (i + 1 >= S.size() || S[i] > S[i + 1])
    return 1;
  else
    return 1 + LIS(S, i + 1);
}

int main()
{
  int size, max;

  cin >> size;
  vector<int> input(size);
  max = 0;

  for (int i = 0; i < size; i++) {
    cin >> input[i];
  }

  for (int i = 0; i < size; i++) {
    int res = LIS(input, i);
    max = (res > max) ? res : max;
  }

  cout << max << endl;
}
