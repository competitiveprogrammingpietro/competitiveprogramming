#include <iostream>

using namespace std;

// Source: https://practice.geeksforgeeks.org/problems/longest-common-subsequence/0
int M[101][101] = { {0} };



int test()
{
  string one, two;
  int sone, stwo, lcs = 0;
  cin >> sone >> stwo;
  cin >> one >> two;

  for (int i = 1; i < one.size() + 1; i++) {
    for (int j = 1; j < two.size() + 1; j++) {
      if (one[i - 1] == two[j - 1]) {
	M[i][j] = M[i - 1][j - 1] + 1;
      }
      else if (M[i - 1][j] >= M[i][j - 1]) {
	M[i][j] = M[i - 1][j];
      }
      else {
	M[i][j] = M[i][j - 1];
      }
    }
  }

  for (int i = 0; i < one.size() + 1; i++) {
    for (int j = 0; j < two.size() + 1; j++) {
      //      cout << M[i][j] << " ";
      lcs = (M[i][j] > lcs) ? M[i][j] : lcs;
    }
    //cout << endl;
  }
  cout << lcs << endl;
  return 0;
}

int main()
{
  int tests;

  cin >> tests;

  for (auto i = 0; i < tests; i++)
    test();
}
