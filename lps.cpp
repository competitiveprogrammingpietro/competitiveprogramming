#include <iostream>
#include <vector>
#include <string>

using namespace std;
int N[1000][1000] = {{ -1 }};

void test(string input, int i, int j)
{
  if (N[i][j] != -1)
    return;
  
  if (i > j) {
    N[i][j] =  0;
  }
  else if (i == j) {
    N[i][j] = 1;
  }
  else if (input[i] == input[j]) {
     test(input, i + 1, j - 1);
     N[i][j] = 2 + N[i + 1][j - 1];
  }
  else {
    test(input, i + 1, j);
    test(input, i, j - 1);
    N[i][j] =  max(N[i + 1][j], N[i][j - 1]);
  }
  //  cout << "(" << i << "," << j << ") " << N[i][j] << endl;
}


int main()
{
  int t;

  cin >> t;
  for (int i = 0; i < t; i++) {
    string input;

    cin >> input;
    for (int i = 0; i < input.size(); i++) {
      for (int j = 0; j < input.size(); j++) {
	if (i == j)
	  N[i][j] = 1;
	else
	  N[i][j] = -1;
      }
    }
    test(input, 0, input.size() - 1);
    cout << N[0][input.size() - 1] << endl;
  }
}
