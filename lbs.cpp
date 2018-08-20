#include <iostream>
#include <vector>

using namespace std;

/*
 * Complexity O(n^2)
 * https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence/0
 */


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
    // cout << "-------" << endl;
    // for (int u = 0; u < size; u++) {
    //   cout << ends[u] << endl;
    // }
    // cout << "-------" << endl;
  }
  return next;
}




int test(vector<int>& A)
{
  int n = A.size();
  int i, j;

  // Longest increasing/decreasing subsequence
  int *lis = new int[n];
  int *lds = new int [n];
  for (i = 0; i < n; i++)
    lis[i] = lds[i] = 1;
 
  /* Compute LIS values from left to right */
  for (i = 1; i < n; i++)
    for (j = 0; j < i; j++)
      if (A[i] > A[j] && lis[i] < lis[j] + 1)
	lis[i] = lis[j] + 1;
 
  /* Compute LDS values from right to left */
  for (i = n-2; i >= 0; i--)
    for (j = n-1; j > i; j--)
      if (A[i] > A[j] && lds[i] < lds[j] + 1)
	lds[i] = lds[j] + 1;
 
 
  /* Return the maximum value of lis[i] + lds[i] - 1*/
  int max = lis[0] + lds[0] - 1;
  for (i = 1; i < n; i++)
    if (lis[i] + lds[i] - 1 > max)
      max = lis[i] + lds[i] - 1;
  return max; 
}



int main()
{
  int t;

  cin >> t;

  for (int i = 0; i < t; i++) {
    int size;

    cin >> size;
    vector<int> input(size);
    for (int j = 0; j < size; j++) {
      cin >> input[j];
    }
    int result = test(input);
    cout << result << endl;
  }
    
}
