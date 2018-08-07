#include <iostream>
#include <vector>
#include <string>

using namespace std;
// O(?)

int subproblems[101][101];

int test(string& a, string& b, int la, int lb)
{
  for (int i = 0; i <= la; i++) {
    for (int j = 0; j <= lb; j++) {

      // Insert all remaining chars from b 
      if (i == 0)
	subproblems[i][j] = j;

      // Remove all remanining chars from a
      else if (j==0)
	subproblems[i][j] = i;
 
      // Same char: the solution of this subproblem is equal as the previous one
      else if (a[i-1] == b[j-1])
	subproblems[i][j] = subproblems[i-1][j-1];
       
      else {
	subproblems[i][j] = 1 + min(subproblems[i][j-1],        // Insert
				    min(subproblems[i-1][j],    // Remove
					subproblems[i-1][j-1]));// Replace
      }
    }
  }
  return subproblems[la][lb];
}


int main()
{
  int tests;

  cin >> tests;

  int result = 0;
  for (int i = 0; i < tests; i++) {
    string a, b;
    int la, lb;
    cin >> la >> lb;
    cin >> a >> b;

    result = test(a, b, la, lb);
    cout << result << endl;
  }
  return result;
}
