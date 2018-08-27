#include <iostream>
#include <vector>
#include <string>

// Source : https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence/0
using namespace std;

int test(string input)
{
  int N[1005][1005];

  for (int i = 0; i < input.size(); i++) {
    N[i][i] = 1;
  }

  for (int l = 2; l <= input.size(); l++) {
    for (int i = 0; i < input.size() - l + 1; i++) {
	int j = i + l - 1;
	if (input[i] == input[j] && j == 2)
	  N[i][j] = 2;
	else if (input[i] == input[j]) {
	  N[i][j] = 2 + N[i + 1][j - 1];
	}
	else {
	  N[i][j] =  max(N[i + 1][j], N[i][j - 1]);
	}
      }
  }
  
  // cout << endl;
  // for (int i = 0; i < input.size(); i++) {
  //   for (int j = 0; j < input.size(); j++) {
  //     cout << N[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  return N[0][input.size() - 1];
  //  cout << "(" << i << "," << j << ") " << N[i][j] << endl;
}


int main()
{
  int t;

  cin >> t;
  for (int i = 0; i < t; i++) {
    string input;

    cin >> input;
        int result = test(input);
	//int result = lps(input);
    cout << result << endl;
  }
}
